#pragma once
#ifndef __ADC_SIN_TEST_H
#define __ADC_SIN_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h" 
#include "stdint.h"

/* 外部引用 ADC 句柄 (定义在 adc.c 中) */
extern ADC_HandleTypeDef hadc1;

/* ============================================================ */
/* 宏定义配置                                                   */
/* ============================================================ */
#define ADC_CH_NUM          1      /* 当前仅使用1个通道 (CH1) */
#define ADC_BUFFER_SIZE     1    /* 每个通道缓存的数据量 (根据你的正弦波周期/采样率调整) */

/* 1. 声明全局变量，用来存放DMA搬运过来的数据 */
//extern uint16_t g_adc_dma_buffer[ADC_CH_NUM * ADC_BUFFER_SIZE];
extern uint16_t g_adc_dma_buffer;
/* ============================================================ */
/* Exported Functions (应用层接口)                              */
/* ============================================================ */

/* 3. 封装启动函数 */
void ADC_Sin_Test_Start(void);

/* (可选) 封装停止函数 */
void ADC_Sin_Test_Stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_SIN_TEST_H */