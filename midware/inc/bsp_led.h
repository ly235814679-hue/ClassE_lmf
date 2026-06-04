/*led相关*/
/**
 * @file   bsp_led.h
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
#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h" 
#include "stdint.h"

/* ============================================================ */
/* Exported Functions (应用层接口)                */
/* ============================================================ */
void led1_on(void);
void led1_off(void);
void led1_toggle(void);
void led2_on(void);
void led2_off(void);
void led2_toggle(void);
#ifdef __cplusplus
}
#endif

#endif /* __BSP_LED_H */