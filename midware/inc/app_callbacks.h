/**
 * @file    app_callbacks.h
 * @brief   HAL库外设回调函数的集中处理与分发层
 * 
 * @details
 * 该文件实现HAL库的弱定义回调函数重写。
 * 主要作用是连接驱动层(HAL)和应用层(App)
 * 1. 捕获底层中断事件（定时器溢出、ADC转换完成、UART接收完成等）
 * 2. 根据外设实例 (Instance) 进行过滤
 * 3. 设置应用层的状态标志位或移动数据缓冲区
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-24
 * @version v1.0.0
 * 
 * @copyright xxx
 * 
 * @note
 * 由于这些函数在中断上下文(ISR)中执行，请遵守以下原则：
 * - 禁止使用耗时的阻塞操作 (如 HAL_Delay, 长循环)。
 * - 禁止执行浮点运算（除非确认FPU在中断中已保存上下文）。
 * - 保持代码尽可能短，复杂逻辑请置位标志后在主循环处理。
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-12-24 | v1.0.0  | Yuan Jiawen | 初始版本             |
 */

#pragma once
#ifndef __APP_CALLBACKS_H
#define __APP_CALLBACKS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h" 
#include "stdint.h"

/* 标志使用volatile关键字，因为这些变量会在中断/回调中被修改 */
extern volatile uint8_t UART_RX_BUFFER[64];
extern volatile uint8_t UART_TX_BUFFER[32];
extern volatile uint16_t ADC_CONVERSION_BUFFER[16];

/* ============================================================ */
/* Exported Functions (应用层接口)                */
/* ============================================================ */


void App_Callbacks_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_CALLBACKS_H */