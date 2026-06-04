#ifndef __BSP_FAN_PID_H
#define __BSP_FAN_PID_H

#include "stm32f1xx_hal.h"
#include "PID.h" 

/* PID 参数宏定义 - 需要根据实际散热系统进行调优 */
#define FAN_PID_KP        5.0f   // 比例系数
#define FAN_PID_KI        0.2f   // 积分系数
#define FAN_PID_KD        0.1f   // 微分系数
#define FAN_PID_TAU       0.02f  // 微分低通滤波时间常数
#define FAN_PID_T         0.5f   // 采样周期(秒)，每500ms调用一次

/* 目标温度默认值 */
#define DEFAULT_TARGET_TEMP  120.0f

/* PWM 限制定义 */
#define FAN_PWM_MIN       20.0f  // 20% 最小占空比
#define FAN_PWM_MAX       100.0f // 100% 最大占空比

/* 积分限制 (抗饱和) */
#define FAN_INT_MAX       50.0f
#define FAN_INT_MIN       -50.0f

typedef struct {
    TIM_HandleTypeDef *htim; // 指向HAL定时器句柄
    uint32_t channel;        // PWM通道
    float targetTemp;        // 目标保持温度
    PIDController pid;       // PID控制器实例
} FanControl_t;

/* 可视变量 */
extern FanControl_t Fan1;
extern TIM_HandleTypeDef htim3;
/* 函数声明 */
void Fan_PID_Init(FanControl_t *fan, TIM_HandleTypeDef *htim, uint32_t channel);
void Fan_Set_Target_Temp(FanControl_t *fan, float temp);
void Fan_Process_Temp(FanControl_t *fan, float currentTemp);
uint8_t Fan_SetSpeed_PID_Turn_Off(TIM_HandleTypeDef *htim,float duty_cycle);

#endif /* __BSP_FAN_PID_H */