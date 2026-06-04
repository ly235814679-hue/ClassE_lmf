/**
 * @file    bsp_ringbuffer.h
 * @brief   环形缓冲区的管理
 * 
 * @details
 * 该文件实现所有环形缓冲区的初始化、大小定义等
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-25
 * @version v1.0.0
 * 
 * @copyright xxx
 * 
 * @note
 *    暂无
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-12-25 | v1.0.0  | Yuan Jiawen | 初始版本             |
 */
#pragma once
#ifndef BSP_RB_H
#define BSP_RB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lwrb.h"

/* Defines -------------------------------------------------------------------*/
/* 缓冲区的大小 */
#define BSP_UART_RB_SIZE     512U
#define BSP_SPI_RB_SIZE      256U
#define BSP_ADC_RB_SIZE      256U
/* Global Handles ------------------------------------------------------------*/
extern lwrb_t rb_uart;
extern lwrb_t rb_spi;
extern lwrb_t rb_adc;

/* Function Prototypes -------------------------------------------------------*/
/**
 * @brief  初始化所有定义的环形缓冲区
 * @note   main() 的初始化阶段调用
 */
void BSP_RB_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_RB_H */