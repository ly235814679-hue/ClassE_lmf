/*继电器相关函数*/
#include "bsp_relay.h"

/* * 硬件配置 
 * 顺序对应：通道1 (Bit0), 通道2 (Bit1), 通道3 (Bit2), 通道4 (Bit3)
 */
static const Relay_GPIO_t Relay_Map[RELAY_COUNT] = {
    {RELAY_1_GPIO_Port, RELAY_1_Pin}, // Relay 1 ,PA12
    {RELAY_2_GPIO_Port, RELAY_2_Pin}, // Relay 2 ,PA11
    {RELAY_3_GPIO_Port, RELAY_3_Pin}, // Relay 3 ,PA10
    {RELAY_4_GPIO_Port, RELAY_4_Pin}  // Relay 4 ,PA9
};

/**
  * @brief  初始化继电器GPIO
  * @note   用于确保初始状态。
  */
void Relay_Init(void)
{
    /* 遍历所有通道，默认初始化为关闭状态 (低电平) */
    for (int i = 0; i < RELAY_COUNT; i++)
    {
        /* 确保初始电平为低 (Relay OFF) */
        HAL_GPIO_WritePin(Relay_Map[i].Port, Relay_Map[i].Pin, GPIO_PIN_RESET);
    }
}

/**
  * @brief  设置继电器组合状态 (实现16种组合切换)
  * @param  combination: 组合位掩码 (0x00 ~ 0x0F)
  * Bit 0 = Relay 1
  * Bit 1 = Relay 2
  * Bit 2 = Relay 3
  * Bit 3 = Relay 4
  * 1 = Enable (High), 0 = Disable (Low)
  */
void Relay_Set_Combination(uint8_t combination)
{
    for (int i = 0; i < RELAY_COUNT; i++)
    {
        /* 检查 combination 的第 i 位是否为 1 */
        if (combination & (1 << i))
        {
            /* 该位为1，输出高电平，使能继电器 */
            HAL_GPIO_WritePin(Relay_Map[i].Port, Relay_Map[i].Pin, GPIO_PIN_SET);
        }
        else
        {
            /* 该位为0，输出低电平，关闭继电器 */
            HAL_GPIO_WritePin(Relay_Map[i].Port, Relay_Map[i].Pin, GPIO_PIN_RESET);
        }
    }
}