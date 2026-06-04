#include "bsp_soft_timer.h"
#include "MultiTimer.h"
#include "app_event.h"


/* ============================================================ */
/* Private Variables                    */
/* ============================================================ */

// 64位计数器
static volatile uint64_t g_soft_timer_ticks = 0;

// 定时器句柄
static MultiTimer timer_pid;
static MultiTimer timer_debug;
static MultiTimer timer_temp;

/* ============================================================ */
/* Private Function Prototypes         */
/* ============================================================ */

static uint64_t PlatformTicks_Get(void);
static void Callback_TempPidUpdate(MultiTimer* timer, void* userData);
static void Callback_Debug(MultiTimer* timer, void* userData);
static void Callback_GET_TEMP(MultiTimer* timer, void* userData);

/* ============================================================ */
/* Public Function Implementation */
/* ============================================================ */

/**
 * @brief  在中断中递增计数器
 * @note   在stm32f1xx_it.c的 SysTick_Handler中调用
 */
void BSP_SoftTimer_IncTick(void)
{
    g_soft_timer_ticks++;
}

/**
 * @brief  初始化函数
 */
void BSP_SoftTimer_Init(void)
{
    // 1. 注册时基获取函数
    multiTimerInstall(PlatformTicks_Get);

    // 2. 创建并启动任务 (500ms 周期)
//    multiTimerStart(&timer_pid, 500, Callback_TempPidUpdate, NULL);

    // 3. 创建并启动任务
//    multiTimerStart(&timer_debug, 20000, Callback_Debug, NULL);
//    
//    // 4.创建并启动温度读取任务
//    multiTimerStart(&timer_temp, 100, Callback_GET_TEMP, NULL);
}

/**
 * @brief  主循环处理函数
 */
void BSP_SoftTimer_Process(void)
{
    multiTimerYield();
}

/* ============================================================ */
/* Private Function Implementation */
/* ============================================================ */

/**
 * @brief  获取64位时间戳
 * @return uint64_t 当前毫秒数
 */
static uint64_t PlatformTicks_Get(void)
{
    uint64_t ticks;
    // 关闭中断，防止读取过程中被SysTick打断导致高低位不一致
    __disable_irq(); 
    
    ticks = g_soft_timer_ticks;
    
    // 恢复中断
    __enable_irq();

    return ticks;
}

/**
 * @brief  周期温度读取+PID控制参数更新回调
 */
static void Callback_TempPidUpdate(MultiTimer* timer, void* userData)
{        
    app_event_send(EVT_TEMP_READ_START,1);
//    multiTimerStart(timer, 500, Callback_TempPidUpdate, userData);
}

/**
 * @brief  回调
 */
static void Callback_Debug(MultiTimer* timer, void* userData)
{        
    
    app_event_send(EVT_DEBUG,0);
//    multiTimerStart(timer, 20000, Callback_Debug, userData);
}

static void Callback_GET_TEMP(MultiTimer* timer, void* userData)
{        
    app_event_send(EVT_GET_TEMP,0);
//    multiTimerStart(timer, 100, Callback_GET_TEMP, userData);
}