
#include "main.h"
#include "dwt_delay.h"
#include <stdio.h> // 用于printf调试，仅演示

// 定义一个测量对象
DWT_Time_t measureObj;

int main(void)
{
		HAL_Init();
		SystemClock_Config(); // 配置好系统时钟

		// 1. 初始化 DWT (务必在时钟配置SystemClock_Config()后调用)
		DWT_Init();

		while (1)
		{
				// ------------------------------------
				// 示例 1: 使用微秒延时 (例如翻转IO)
				// ------------------------------------
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
				DWT_Delay_us(50); // 延时 50us
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
				DWT_Delay_us(50);
				
				// ------------------------------------
				// 示例 2: 测量某段代码执行时间
				// ------------------------------------
				
				DWT_Time_Start(&measureObj); // 开始计时
				
				// --- 待测代码段 ---
				HAL_Delay(500); // 模拟一个耗时操作 (HAL库的ms延时)
				// -----------------
				
				DWT_Time_Stop(&measureObj); // 停止计时
				
				// 打印结果
				// 理论上应该接近 500000 us (加上一点函数调用开销)
				printf("Ticks: %lu, Time: %.2f us\r\n", 
							 measureObj.duration_tick, 
							 measureObj.duration_us);
							 
				DWT_Delay_ms(1000); 
		}
}

