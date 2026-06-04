/**
 * @file         :bsp_soft_timer.h
 * @brief     :基于MultiTimer的软件定时器中间层
 *
 * @details
 * 本模块实现了MultiTimer库在STM32上的板级支持
 * 封装 MultiTimer的初始化与轮询接口
 * 提供时基
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-24
 * @version v1.0.0
 * 
 * @copyright xxx
 * 
 * @note
 * 1. 移植要求：必须在stm32f1xx_it.c的SysTick_Handler中调用@ref BSP_SoftTimer_IncTick()。
 * 2. 并发安全：底层计数器变量使用volatile修饰，且读取时使用了临界区保护。
 * 3. 实时性：回调函数执行时间不宜过长
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-12-24 | v1.0.0  | Yuan Jiawen | 初始版本             |
 */

#pragma once
#ifndef __BSP_SOFT_TIMER_H
#define __BSP_SOFT_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* ============================================================ */
/* Exported Functions                  */
/* ============================================================ */

/**
 * @brief  初始化软件定时器模块
 */
void BSP_SoftTimer_Init(void);

/**
 * @brief  软件定时器主循环处理 (在while(1)中调用)
 */
void BSP_SoftTimer_Process(void);

/**
 * @brief  提供给SysTick_Handler调用的计数接口
 * @note   不要在其他地方调用此函数
 */
void BSP_SoftTimer_IncTick(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SOFT_TIMER_H */