#include "ADC_sin_test.h"

/* 
* 1. 定义全局变量：用于存放DMA搬运过来的ADC数据
 */
//uint16_t g_adc_dma_buffer[ADC_CH_NUM * ADC_BUFFER_SIZE] = {0};
uint16_t g_adc_dma_buffer;
/**
  * @brief  启动 ADC 和 DMA 循环采集
  */
void ADC_Sin_Test_Start(void)
{
    /*
     * HAL_ADC_Start_DMA 参数说明：
     * 参数1: &hadc1 -> 使用的ADC硬件句柄
     * 参数2: (uint32_t *)g_adc_dma_buffer -> DMA搬运的目标内存首地址
     * 参数3: ADC_CH_NUM * ADC_BUFFER_SIZE -> DMA需要搬运的总数据量 (16位为单位)
     */
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&g_adc_dma_buffer, (ADC_CH_NUM * ADC_BUFFER_SIZE));
}

/**
  * @brief  停止 ADC 和 DMA 采集
  */
void ADC_Sin_Test_Stop(void)
{
    HAL_ADC_Stop_DMA(&hadc1);
}