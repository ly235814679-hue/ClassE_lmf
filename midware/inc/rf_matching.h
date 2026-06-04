#ifndef __RF_MATCHING_H
#define __RF_MATCHING_H

#include "main.h"
#include "bsp_sys_ctrl.h"
/* 配置参数 */
#define RELAY_COMB_MAX      16      // 16种组合 (0x00 - 0x0F)
#define ADC_SAMPLE_AVG      20      // ADC采样平均次数
#define RELAY_STABLE_MS     100     // 继电器机械稳定延时
#define RF_SETTLE_MS        20      // 射频开启后稳定延时
#define ADC_VREF            3.3f    // ADC 参考电压
#define ADC_MAX_VALUE       4095.0f // 12位ADC的最大值 (2^12 - 1)


/* 接口 */
HAL_StatusTypeDef RF_Matching_Optimize(void);

#endif /* __RF_MATCHING_H */