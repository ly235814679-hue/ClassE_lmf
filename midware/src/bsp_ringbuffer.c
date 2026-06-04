/**
 * @file    bsp_rb.c
 * @brief   环形缓冲区管理
 */

#include "bsp_ringbuffer.h"

/* 1. 定义 UART 使用的环形缓冲区及数据区 */
lwrb_t rb_uart;
static uint8_t rb_uart_data[BSP_UART_RB_SIZE];

/* 2. 定义 SPI 使用的环形缓冲区及数据区 */
lwrb_t rb_spi;
static uint8_t rb_spi_data[BSP_SPI_RB_SIZE];

/* 3. 定义 ADC 使用的环形缓冲区及数据区 */
lwrb_t rb_adc;
static uint8_t rb_adc_data[BSP_ADC_RB_SIZE];

/**
 * @brief  初始化所有定义的环形缓冲区
 */
void BSP_RB_Init(void) {
    
    /* 初始化 UART 缓冲区 */
    /* lwrb_init(lwrb_t* buff, void* buffdata, size_t size) */
    lwrb_init(&rb_uart, rb_uart_data, sizeof(rb_uart_data));

    /* 初始化 SPI 缓冲区 */
    lwrb_init(&rb_spi, rb_spi_data, sizeof(rb_spi_data));
    
    /* 初始化 ADC 缓冲区 */
    lwrb_init(&rb_spi, rb_adc_data, sizeof(rb_adc_data));
}
