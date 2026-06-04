#include "bsp_sys_ctrl.h"
#include "bsp_led.h"

/**
  * @brief  系统控制IO初始化
  */
void Sys_Ctrl_Init(void)
{
    PWR_OFF();    
    SIG_OFF();
}

/**
  * @brief  开启系统
  * @note   时序：电源开启 -> 信号开启
  */
void Sys_Start(void)
{
    /* 1. 开启电源 */
    PWR_ON();

    /* 2. 开启信号 */
    SIG_ON();
}

/**
  * @brief  关闭系统
  * @note   时序：电源关闭 -> 信号关闭 (根据用户指定顺序)
  */
void Sys_Stop(void)
{
    /* 1. 关闭电源 */
    PWR_OFF();
    
        /* 2. 等待一会... */
    DWT_Delay_us(50);
    
        /* 3. 关闭信号源 */
    SIG_OFF();
}

 /**
  * @brief  脉冲与冷却时序控制
  */
void Cool_Pulse_ctr(uint8_t Pulse_count)
{
    uint8_t i;
    /* 1. 预冷却 */
    HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_RESET);
    
    /* 2. 加热时冷却 */
    for(i=0;i<Pulse_count;i++)
    {
        HAL_Delay(200);
        led1_toggle();
        HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_SET);
        SIG_ON();
        HAL_Delay(50);
        SIG_OFF();
        HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_RESET);
    }

    /* 3. 后冷却 */
    HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_RESET);
}

