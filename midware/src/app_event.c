/**
 * @file    app_event.c
 * @brief   基于 LwRB 的简易事件循环库实现
 */


//#include "app_event.h"
//#include "stm32f10x.h"  

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "dwt_delay.h"
#include "bsp_multibutton.h"
#include "bsp_soft_timer.h"
#include "app_event.h"
#include "bsp_fan_pid.h"
#include "bsp_relay.h"
#include "bsp_sys_ctrl.h"
#include "rf_matching.h"


/* ================= 宏定义与私有变量 ================= */

/* 临界区保护宏：适配裸机 
 * LwRB 文档指出：多写入入口(Main+IRQ)必须进行写保护
 */
#define ENTER_CRITICAL()    __disable_irq()
#define EXIT_CRITICAL()     __enable_irq()

/* 定义 LwRB 句柄 */
static lwrb_t evt_rb;

/* 定义实际存储数据的内存池 */
static uint8_t evt_rb_data[APP_EVENT_QUEUE_SIZE];

/* ================= 函数实现 ================= */

/**
 * @brief  初始化事件系统
 */
uint8_t app_event_init(void) {
    /* 初始化环形缓冲区 */
    if (lwrb_init(&evt_rb, evt_rb_data, sizeof(evt_rb_data))) {
        return 1; /* 初始化成功 */
    }
    return 0; /* 初始化失败 */
}

/**
 * @brief  发送一个事件到队列
 */
uint8_t app_event_send(app_evt_type_t type, uint32_t param) {
    app_evt_t evt;
    size_t written_len;
    
    evt.type = type;
    evt.param = param;

    /* 进入临界区：防止高优先级中断打断写入操作导致数据损坏 */
    ENTER_CRITICAL();
    
    /* 写入数据到环形缓冲区 */
    written_len = lwrb_write(&evt_rb, &evt, sizeof(app_evt_t));
    
    EXIT_CRITICAL();

    /* 检查是否写入了完整的一个结构体大小 */
    return (written_len == sizeof(app_evt_t)) ? 1 : 0;
}

/**
 * @brief  处理挂起的事件 (消费者)
 */
void app_event_process(void) {
    app_evt_t evt;

    /* 尝试从缓冲区读取一个事件 
     * 因为只有一个消费者(主循环)，读取操作不需要临界区保护
     */
    if (lwrb_read(&evt_rb, &evt, sizeof(app_evt_t)) == sizeof(app_evt_t)) {
        /* 调用用户定义的回调函数处理事件 */
        app_event_handler(&evt);
    }
}

/**
 * @brief  弱定义的回调函数，防止用户未定义时编译报错
 */
__attribute__((weak)) void app_event_handler(const app_evt_t* evt) {
    (void)evt; /* 防止未使用参数警告 */
//    /* 默认不执行任何操作，用户应重写此函数 */

}