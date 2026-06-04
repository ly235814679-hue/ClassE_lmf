#pragma once
#ifndef __BSP_SYS_CTRL_H
#define __BSP_SYS_CTRL_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "dwt_delay.h"
/* ============================================================ */
/* BSRR寄存器操作                            */
/* ============================================================ */
/* BSRR 低16位写1 -> Set (输出高)
 * BSRR 高16位写1 -> Reset (输出低)
 */

/* 电源 (Active High: High=ON, Low=OFF) */
#define PWR_ON()      (SYS_PWR_Port->BSRR = SYS_PWR_Pin)
#define PWR_OFF()     (SYS_PWR_Port->BSRR = (uint32_t)SYS_PWR_Pin << 16U)

/* 信号 (Active Low: Low=ON, High=OFF) */
/* 开启：输出低电平 */
#define SIG_ON()      (SYS_SIG_Port->BSRR = (uint32_t)SYS_SIG_Pin << 16U)
/* 关闭：输出高电平 (OD模式下为高阻，靠外部上拉到高) */
#define SIG_OFF()     (SYS_SIG_Port->BSRR = SYS_SIG_Pin)

/* ============================================================ */
/* 函数声明                                                     */
/* ============================================================ */

void Sys_Ctrl_Init(void);
void Sys_Start(void);
void Sys_Stop(void);
void Cool_Pulse_ctr(uint8_t Pulse_count);
void Impedance_Matching_Switching(void);

#endif /* __BSP_SYS_CTRL_H */