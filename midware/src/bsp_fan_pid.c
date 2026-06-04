#include "bsp_fan_pid.h"

FanControl_t Fan1;
/**
 * @brief  初始化风扇控制及PID
 * @param  fan: 风扇控制结构体指针
 * @param  htim: 定时器句柄指针 (如 &htim3)
 * @param  channel: PWM通道 (如 TIM_CHANNEL_1)
 */
void Fan_PID_Init(FanControl_t *fan, TIM_HandleTypeDef *htim, uint32_t channel) {
    fan->htim = htim;
    fan->channel = channel;
    fan->targetTemp = DEFAULT_TARGET_TEMP;

    /* 1. 初始化 PID 参数结构体 */
    /* 使用上传文件 PID.h 中的结构成员 */
    fan->pid.Kp = FAN_PID_KP;
    fan->pid.Ki = FAN_PID_KI;
    fan->pid.Kd = FAN_PID_KD;
    fan->pid.tau = FAN_PID_TAU;
    
    /* 设定输出限制 20% ~ 100% */
    fan->pid.limMin = FAN_PWM_MIN;
    fan->pid.limMax = FAN_PWM_MAX;
    
    /* 设定积分限制 */
    fan->pid.limMinInt = FAN_INT_MIN;
    fan->pid.limMaxInt = FAN_INT_MAX;
    
    /* 设定采样时间 */
    fan->pid.T = FAN_PID_T;

    /* 2. 调用库函数初始化内部变量 (integrator, prevError等) */
    PIDController_Init(&fan->pid); 

    /* 3. 启动 PWM 并设置默认占空比为 20% */
    HAL_TIM_PWM_Start(fan->htim, fan->channel);
    
    // 计算 CCR 值: (ARR+1) * 0.2
    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(fan->htim);
    uint32_t default_ccr = (uint32_t)((arr + 1) * (FAN_PWM_MIN / 100.0f));
    
    __HAL_TIM_SET_COMPARE(fan->htim, fan->channel, default_ccr);
}

/**
 * @brief  修改目标温度
 */
void Fan_Set_Target_Temp(FanControl_t *fan, float temp) {
    fan->targetTemp = temp;
}

/**
 * @brief  处理函数：传入当前温度，自动计算并更新PWM
 * @note   请确保调用此函数的频率与 FAN_PID_T 定义的时间一致 (例如在定时器中断中每500ms调用一次)
 * @param  currentTemp: 当前测量到的温度
 */
void Fan_Process_Temp(FanControl_t *fan, float currentTemp) {

    
    float pid_output_percent = PIDController_Update(&fan->pid, currentTemp, fan->targetTemp); //

    /* 将 PID 输出的百分比 (float) 转换为 PWM 比较寄存器值 (int) */
    /* 优化：尽量减少除法，ARR通常是固定的，可以在初始化时预存 float 缩放因子，这里直接使用标准计算 */
    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(fan->htim);
    
    /* 公式: CCR = (ARR + 1) * (Duty / 100) */
    uint32_t ccr_val = (uint32_t)((arr + 1) * pid_output_percent * 0.01f);

    /* 更新 PWM */
    __HAL_TIM_SET_COMPARE(fan->htim, fan->channel, ccr_val);
}

/**
* @brief 设置风扇速度（关闭PID直接强制设置占空比）
 * @param htim 定时器句柄
 * @param Channel 定时器通道
 * @param duty_cycle 占空比 (0.0f 到 1.0f)
 * @return uint8_t 1:成功, 0:参数错误
 */
uint8_t Fan_SetSpeed_PID_Turn_Off(TIM_HandleTypeDef *htim,float duty_cycle){

        // 1. 参数校验
    if (duty_cycle < 0.0f) duty_cycle = 0.0f;
    if (duty_cycle > 1.0f) duty_cycle = 1.0f;
        
        // 2. 获取ARR
        uint32_t arr = __HAL_TIM_GET_AUTORELOAD(htim);
    
        // 3. 计算CCR
        uint32_t ccr_val = (uint32_t)((arr + 1) * duty_cycle);
    
        // 4. 设置CCR
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, ccr_val);
    
        // 5. 启动
    
      HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
        return 1;
    
}