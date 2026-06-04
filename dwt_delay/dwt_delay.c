/**
 * @file    dwt_delay.c
 * @brief   基于ARM DWT实现延时
 * 
 * @details
 * 本模块基于ARM-DWT实现us、ms延时和执行时间计时。
 * 执行时间计时功能的分辨率最低1us。
 * 
 * @author  Yuan Jiawem <jw.yuan@nmed.org.cn>
 * @date    2025-11-20
 * @version v1.0.0
 * 
 * @copyright Copyright (c) Yuan Jiawen.
 */
#include "dwt_delay.h"

/**
 * @brief  初始化 DWT 计数器
 * @note   在系统时钟初始化SystemClock_Config()之后调用
 */
void DWT_Init(void)
{
    /* 1. 确保CoreDebug 中的DEMCR(Debug Exception and Monitor Control Register)的TRCENA位置位 */
    /* 这一步是开启DWT单元的前提 */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

#if DWT_SUPPORT_CORTEX_M7
    /* 对于 Cortex-M7 (F7, H7)，需要先解锁 LAR (Lock Access Register) */
    DWT->LAR = 0xC5ACCE55;
#endif

    /* 2. 清除CYCCNT计数器 */
    DWT->CYCCNT = 0;

    /* 3. 开启DWT控制寄存器中的CYCCNTENA位，启动计数器 */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief  微秒级延时
 * @param  us: 延时微秒数
 */
 void DWT_Delay_us(volatile uint32_t us)
{
    uint32_t start_tick = DWT->CYCCNT;
    uint32_t delay_ticks = us * (DWT_CPU_FREQ_HZ / 1000000);

    /* 使用无符号数减法自动处理计数器溢出/回绕问题 */
    /* 只要 delay_ticks 小于 2^32 (约40亿)，此逻辑在溢出时依然有效 */
    while ((DWT->CYCCNT - start_tick) < delay_ticks);
}

/**
 * @brief  毫秒级延时
 * @param  ms: 延时毫秒数
 */
void DWT_Delay_ms(volatile uint32_t ms)
{
    /* 为了防止大数值溢出，循环调用 us 延时或直接计算 */
    /* 只要 ms 不会太大，直接计算更准 */
    for (uint32_t i = 0; i < ms; i++) {
        DWT_Delay_us(1000);
    }
}

/**
 * @brief  开始测量代码执行时间
 * @param  pTime: 指向 DWT_Time_t 结构体的指针
 */
void DWT_Time_Start(DWT_Time_t *pTime)
{
    pTime->start_tick = DWT->CYCCNT;
}

/**
 * @brief  停止测量并计算时间
 * @param  pTime:指向DWT_Time_t结构体的指针
 */
void DWT_Time_Stop(DWT_Time_t *pTime)
{
    pTime->stop_tick = DWT->CYCCNT;
    
    /* 处理溢出并计算差值 */
    /* 2^32 循环计数特性使得直接相减即为真实差值 (无符号运算) */
    pTime->duration_tick = pTime->stop_tick - pTime->start_tick;
    
    /* 转换为时间单位 */
    /* 注意：这里使用了浮点运算，如果对速度极度敏感，请只使用 duration_tick */
    pTime->duration_us = (float)pTime->duration_tick / (DWT_CPU_FREQ_HZ / 1000000.0f);
    pTime->duration_ms = pTime->duration_us / 1000.0f;
}

/**
 * @brief  获取上次测量的时长 (us)
 * @param  pTime: 指向 DWT_Time_t 结构体的指针
 * @return float: 微秒数
 */
float DWT_Get_Duration_Us(DWT_Time_t *pTime)
{
    return pTime->duration_us;
}
