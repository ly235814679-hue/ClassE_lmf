/*温度读取相关函数*/
#include "bsp_get_temp.h"
#include "spi.h" // 引用 hspi2

/* 存储读取到的 12 位 ADC 原始数据 */
uint16_t RF_temp[4] = {0};
uint16_t MOS_temp[4] = {0};

/**
 * @brief  从 MCP3208 指定通道读取 12 位 ADC 值
 * @param  channel: 通道号 (0-7)
 * @retval 12位采样结果 (0-4095)
 */
static uint16_t MCP3208_Read_Channel(uint8_t channel)
{
    uint8_t tx_data[3] = {0};
    uint8_t rx_data[3] = {0};                                   
    uint16_t adc_value = 0;

    /* 构造控制字节 (根据数据手册 Figure 6-1) 
     * Byte 0: 0000 0(Start) (SGL) (D2) -> 0x06 | (D2位)
     * Byte 1: (D1) (D0) X X X X X X   -> (D1 D0左移6位)
     */
    tx_data[0] = 0x06 | ((channel >> 2) & 0x01); // 起始位=1, SGL=1(单端), D2
    tx_data[1] = (channel & 0x03) << 6;          // D1, D0
    tx_data[2] = 0x00;                           // 填充字节用于时钟输出

    /* 选中芯片 (PB12 CS 置低) */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

    /* SPI 传输 */
    if (HAL_SPI_TransmitReceive(&hspi2, tx_data, rx_data, 3, 100) == HAL_OK)
    {
        /* 接收逻辑:
         * Byte 1 的低4位是数据的高4位 (B11-B8)
         * Byte 2 是数据的低8位 (B7-B0)
         */
        adc_value = ((rx_data[1] & 0x0F) << 8) | rx_data[2];
    }

    /* 释放芯片 (PB12 CS 置高) */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    return adc_value;
}

/**
 * @brief  获取 CH0-CH3 的数据到 RF_temp
 */
void Get_RF_temp(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        RF_temp[i] = MCP3208_Read_Channel(i); // 读取通道 0, 1, 2, 3
    }
}

/**
 * @brief  获取 CH4-CH7 的数据到 MOS_temp
 */
void Get_MOS_temp(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        MOS_temp[i] = MCP3208_Read_Channel(i + 4); // 读取通道 4, 5, 6, 7
    }
}