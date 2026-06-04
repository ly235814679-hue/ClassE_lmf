/**
 * @file    dwt_delay.h
 * @brief   DWT延时功能头文件
 * 
 * @details
 * 本模块提供系统所有的宏配置、结构体定义、初始化和延时接口。
 * 理论支持任意ARM CORTEX-M芯片。
 * 
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-24
 * @version v1.0.1
 * 
 * @copyright Copyright (c) Yuan Jiawen.
 * 
 * @note
 * 1. Cortex-M7和其他内核配置不同，需配置DWT_SUPPORT_CORTEX_M7以启用
 * 2. 最小延时时间1us，可能存在执行开销(例如F103等实测存在0.5us执行开销)，如果开销敏感，建议优化编译等级，同时改为内联函数，但该问题无法完全避免
 * 3. 如果需要使用内联，请在.h文件中实现函数并删除.c文件中的实现，建议使用如下格式：(强制内联，避免编译器等级不同导致内联忽略)
 *        __attribute__((always_inline)) static inline void DWT_Delay_us(volatile uint32_t us)
 *    {
 *        // ... 代码同上
 *    }
 * 4. 最小执行时间测量结果单位为1us，可能存在开销
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-11-20 | v1.0.0  | Yuan Jiawen | 初始版本             |
 * | 2025-12-24 | v1.0.1  | Yuan Jiawen | 注释修改             |
 */
#pragma once
#ifndef __DWT_DELAY_H
#define __DWT_DELAY_H

#include <stdint.h>
#include "main.h" // 包含以获取 SystemCoreClock

/* =================================================== */

/* * 默认使用 CMSIS 定义的 SystemCoreClock 变量
 * 如果工程中时钟是固定的，可以直接定义数值（如 72000000）
 */
#ifndef DWT_CPU_FREQ_HZ
#define DWT_CPU_FREQ_HZ    (SystemCoreClock) 
#endif

/* 是否支持 Cortex-M7 (如 STM32F7, H7) 
 * M7 需要解锁 LAR 寄存器才能使用 DWT
 * 0: 不开启 (F1/F4等)
 * 1: 开启 (F7/H7等)
 */
#define DWT_SUPPORT_CORTEX_M7   0

/* ================================================ */

/**
 * @brief 时间测量结构体
 */
typedef struct {
    uint32_t start_tick;
    uint32_t stop_tick;
    uint32_t duration_tick;
    float    duration_us;
    float    duration_ms;
} DWT_Time_t;

/* 函数声明 */
void DWT_Init(void);
void DWT_Delay_us(volatile uint32_t us);
void DWT_Delay_ms(volatile uint32_t ms);

/* 执行时间测量函数 */
void DWT_Time_Start(DWT_Time_t *pTime);
void DWT_Time_Stop(DWT_Time_t *pTime);
float DWT_Get_Duration_Us(DWT_Time_t *pTime);

#endif /* __DWT_DELAY_H */


