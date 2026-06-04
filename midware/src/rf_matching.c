#include "math.h"
#include "rf_matching.h"
#include "adc.h"
#include "tim.h"


extern void Relay_Set_Combination(uint8_t combination);
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3; // 假设射频PWM使用htim3

volatile uint8_t count =0;
volatile float Best_vswr =0.0f;
volatile uint8_t best_comb = 0;
volatile uint16_t ADC_0 = 0;
volatile uint16_t ADC_1 = 0;
volatile uint32_t fwd_raw = 0;
volatile uint32_t ref_raw = 0;
volatile float vswr = 0.0f;



/**
 * @brief  私有函数：获取指定ADC通道的平均值 (阻感/驻波比检测)
 * @param  Channel: ADC_CHANNEL_0 或 ADC_CHANNEL_1
 */
static uint32_t Get_ADC_Average(uint32_t Channel) {
        
        //配置ADC通道
    uint32_t sum = 0;
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = Channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5; 
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) return 0;
        //开始遍历
    for (int i = 0; i < ADC_SAMPLE_AVG; i++) {
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
            sum += HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);
    }
    return sum / ADC_SAMPLE_AVG;
}






/**
 * @brief 私有函数，将 12位 ADC 采样原始值转换为对应的输入功率 (dBm)
 * * @param adc_raw ADC 采样的 12 位原始数据 (0 ~ 4095)
 * @return float  对应的输入功率 (单位: dBm)
 */
static float Voltage_to_dbm(uint16_t adc_raw) {
    // 1. 将 12 位 ADC 原始值转换为单片机引脚上的电压 (V_pin)
    float v_pin = ((float)adc_raw / ADC_MAX_VALUE) * ADC_VREF;

    // 2. 根据调理电路，反推 AD8310 芯片 VOUT 脚直出的真实电压
    // 你的逻辑: v_pin = (v_ad8310 / 1.2) + 1.67
    // 反推公式: v_ad8310 = (v_pin - 1.67) * 1.2
    float v_ad8310 = (v_pin - 1.67f) * 1.2f;

    // 3. 根据 AD8310 数据手册的典型参数计算功率
    const float V_SLOPE = 0.024f;     // 斜率为 24 mV/dB (0.024 V/dB) [cite: 5]
    const float P_INTERCEPT = -95.0f; // 50欧姆系统下的截距为 -95 dBm [cite: 75]

    // 根据公式: Pin = (V_ad8310 / Slope) + Intercept [cite: 786]
    float dbm = (v_ad8310 / V_SLOPE) + P_INTERCEPT;
    
    return dbm;
}


/**
 * @brief 私有函数，通过线性功率（W/mW）计算驻波比 (VSWR)
 * * @param p_forward  前向功率 (单位必须与反向功率一致，如均为 W 或 mW)
 * @param p_reflect  反向功率 (单位必须与前向功率一致)
 * @return float     驻波比 (VSWR) 数值，范围 [1.0, 稳定趋于正无穷]
 */
static float Calculate_VSWR_Linear(float p_forward, float p_reflect) {
    // 边界条件处理
    if (p_forward <= 0.0f) {
        return 99.9f; // 如果没有前向功率，返回一个代表极大驻波的错误值
    }
    if (p_reflect <= 0.0f) {
        return 1.0f;  // 理论上无反射时，驻波比为 1.0
    }
    if (p_reflect >= p_forward) {
        return 99.9f; // 全反射或数据异常
    }

    // 计算电压反射系数 |Gamma| = sqrt(P_reflect / P_forward)
    float gamma = sqrtf(p_reflect / p_forward);

    // 计算 VSWR = (1 + |Gamma|) / (1 - |Gamma|)
    float vswr = (1.0f + gamma) / (1.0f - gamma);

    return vswr;
}


/**
 * @brief  自动遍历继电器组合，寻找反射功率最小的最佳点
 * @note   包含射频保护逻辑：切换前关闭RF，测量时开启小功率
 */
HAL_StatusTypeDef RF_Matching_Optimize(void) {
//    uint8_t best_comb = 0;
    float min_reflect_ratio = 9999.0f;
    
   // 1. 初始化时先关闭射频输出
       Sys_Stop();
   
   for (count = 0; count < RELAY_COMB_MAX; count++) {
       // --- 步骤 A: 冷切换继电器 ---
       Relay_Set_Combination(10);
       HAL_Delay(RELAY_STABLE_MS); // 等待触点吸合稳定

       // --- 步骤 B: 开启低功率探测脉冲 ---
               //todo:添加低功率设置操作
       Sys_Start();
       
       HAL_Delay(RF_SETTLE_MS); // 等待射频建立稳态

       // --- 步骤 C: 采集前向和反向功率 ---
       
       ADC_0 = Get_ADC_Average(ADC_CHANNEL_0);
       ADC_1 = Get_ADC_Average(ADC_CHANNEL_1);

       fwd_raw = Voltage_to_dbm(ADC_0);
       ref_raw = Voltage_to_dbm(ADC_1);
       
    //    uint32_t fwd_raw= Voltage_to_dbm(ADC_0);
    //    uint32_t ref_raw= Voltage_to_dbm(ADC_1);

//       uint32_t fwd_raw = Voltage_to_dbm(Get_ADC_Average(ADC_CHANNEL_0)); // 将前向电压转换为dBm
//       uint32_t ref_raw = Voltage_to_dbm(Get_ADC_Average(ADC_CHANNEL_1)); // 将反向电压转换为dBm


       // --- 步骤 D: 计算并比较 ---
    //    float vswr = Calculate_VSWR_Linear(fwd_raw, ref_raw);

       if (vswr < Best_vswr) {
           Best_vswr = vswr;
           best_comb = count;
       } 


       // --- 步骤 E: 关闭射频，准备下一次切换 ---
       Sys_Stop();
   }

   // 2. 最终切换到最优组合
//   Relay_Set_Combination(best_comb);
//   HAL_Delay(RELAY_STABLE_MS);



// //    static uint8_t i =0;
//     Relay_Set_Combination(i);
//     i++;
//     if(i==16)
//     {
//         i=0;
//     }

    
    return HAL_OK;
}