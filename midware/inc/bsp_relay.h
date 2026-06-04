/*继电器相关*/
/**
 * @file   bsp_relay.h
 * @brief  
 * 
 * @details
 * 
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-26
 * @version v1.0.0
 * 
 * @copyright xxx
 * 
 * @note
 *
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-12-26 | v1.0.0  | Yuan Jiawen | 初始版本             |
 */
#pragma once
#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H

#include "stm32f1xx_hal.h"
#include "main.h"
/* 继电器数量 */
#define RELAY_COUNT  4

/* 组合掩码宏，方便调用时进行位运算组合 */
#define RELAY_CH1_MSK  (1 << 0) // 对应 bit 0
#define RELAY_CH2_MSK  (1 << 1) // 对应 bit 1
#define RELAY_CH3_MSK  (1 << 2) // 对应 bit 2
#define RELAY_CH4_MSK  (1 << 3) // 对应 bit 3

/* 全开与全关宏 */
#define RELAY_ALL_OFF  0x00
#define RELAY_ALL_ON   0x0F

/* 硬件引脚定义结构体 */
typedef struct {
    GPIO_TypeDef* Port;
    uint16_t      Pin;
} Relay_GPIO_t;

/* 函数声明 */
void Relay_Init(void);
void Relay_Set_Combination(uint8_t combination);

#endif /* __BSP_RELAY_H */