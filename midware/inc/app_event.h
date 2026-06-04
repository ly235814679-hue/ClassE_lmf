/**
 * @file    app_event.h
 * @brief   基于 LwRB 的简易事件循环库
 */
#pragma once
#ifndef APP_EVENT_H
#define APP_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "lwrb.h" 

/* ================= 配置区域 ================= */

/* 定义事件队列的最大容量（必须是 sizeof(app_evt_t) 的整数倍） 
 * 例如：存放 32 个事件
 */
#define APP_EVENT_QUEUE_SIZE    (32 * sizeof(app_evt_t))

/* ================= 类型定义 ================= */

/**
 * @brief  事件类型枚举
 * @note   用户可以在此添加自定义事件
 */
typedef enum {
    EVT_NONE = 0,
    
    /* 系统级事件 */
    EVT_SYS_INIT,                           /*!< 系统初始化完成 */
    EVT_SYS_ERROR,                          /*!< 系统错误 */
    EVT_SYS_TICK,                           /*!< 定时器滴答 */

    /* 用户级事件 */
        EVT_TEMP_READ_START,                    /*!<温度读取请求事件*/
        EVT_TEMP_OVERLIMIT_FAULT,            /*!<温度过大事件*/
        EVT_VSWR_FAULT,                                /*!<反射功率过大错误*/
        EVT_CURRENT_IMBALANCE_FAULT,    /*!<电流不平衡错误*/
        EVT_UART_RX_DATA,                            /*!<串口收到数据*/
        EVT_ADC_SAMPLE_COMPLETE,            /*!<ADC转换完成*/
        EVT_SYS_INIT_DONE,                        /*!<开机事件*/
        EVT_DEBUG,                                            /*!<debug事件*/
        EVT_GET_TEMP,                       /*温度读取，包括射频探头和MOS*/
        EVT_KEY                             /*按键按下，打5发脉冲，包括前冷却和后冷却*/
    
    /* 在此添加... */
    
} app_evt_type_t;

/**
 * @brief  通用事件结构体
 * @note   为了保证环形缓冲区的性能，结构体大小最好固定且对齐
 */
typedef struct {
    app_evt_type_t type;  /*!< 事件类型 */
    uint32_t       param; /*!< 事件参数 (数据/指针/标志位) */
} app_evt_t;

/* ================= 函数声明 ================= */

/**
 * @brief  初始化事件系统
 * @return 1: 成功, 0: 失败
 */
uint8_t app_event_init(void);

/**
 * @brief  发送一个事件到队列 (线程安全，可在中断中调用)
 * @param  type:  事件类型
 * @param  param: 事件参数 (32位整数，可以是数据或指针)
 * @return 1: 发送成功, 0: 队列已满(发送失败)
 */
uint8_t app_event_send(app_evt_type_t type, uint32_t param);

/**
 * @brief  处理挂起的事件 (需要在主循环中不断轮询)
 * @note   当队列中有事件时，会自动调用 app_event_handler()
 */
void app_event_process(void);

/**
 * @brief  事件处理回调函数 (用户需在主程序中实现此函数)
 * @param  evt: 接收到的事件指针
 */
void app_event_handler(const app_evt_t* evt);

#ifdef __cplusplus
}
#endif

#endif /* APP_EVENT_H */