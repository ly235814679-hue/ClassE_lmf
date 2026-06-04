#ifndef __BSP_BSP_GET_RF_TEMP
#define __BSP_BSP_GET_RF_TEMP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "stdint.h"

/* ============================================================ */
/* 外部变量声明                                                 */
/* ============================================================ */
extern uint16_t RF_temp[4];
extern uint16_t MOS_temp[4];

/* ============================================================ */
/* Exported Functions (应用层接口)                              */
/* ============================================================ */
void Get_RF_temp(void);
void Get_MOS_temp(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_BSP_GET_RF_TEMP */