/* app_callbacks.c */
#include "app_callbacks.h"
#include "usart.h"  
#include "adc.h"    
#include "tim.h"    
#include "multi_button.h"
#include "bsp_ringbuffer.h"
#include "app_event.h"
#include "bsp_led.h"
#include "bsp_relay.h"
#include "rf_matching.h"
#include "command_parser.h"
#include "bsp_get_temp.h"

// 定义缓冲区
volatile uint8_t UART_RX_BUFFER[64];                //串口接收缓冲区

volatile uint8_t UART_TX_BUFFER[32];                //串口发送缓冲区
volatile uint16_t ADC_CONVERSION_BUFFER[16];//ADC数据缓冲区
volatile uint16_t ADC_DATA[16];                            //ADC采集到的数据
volatile uint16_t SPI_READ_BUFFER[16];            //SPI数据读取缓冲区
volatile uint16_t SPI_DATA[16];                            //SPI读取到的数据
/* ============================================================ */
/* Callback Implementations (回调重写)            */
/* ============================================================ */

/**
  * @brief  定时器更新中断回调
  * @param  htim: 定时器句柄指针
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    
    if(htim->Instance == TIM1){
    
        button_ticks();
    }
}

/**
  * @brief  UART DMA/中断 接收完成回调
  * @param  huart: 串口句柄指针
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

    
}

/**
  * @brief  ADC DMA 转换完成回调
  * @param  hadc: ADC句柄指针
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){

}
/**
  * @brief  获取DMA数据长度
  * @param  hadc: DMA句柄指针
  */
static uint16_t getRxLen(DMA_HandleTypeDef *dma_rx)
{
    uint16_t len;
    len = BSP_UART_RB_SIZE - __HAL_DMA_GET_COUNTER(dma_rx);
    return len;
}
/**
  * @brief  错误回调，用于调试
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){

    
}
/**
  * @brief  UART接收事件回调
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance == USART2){
    
        if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
        
            lwrb_write(&rb_uart,(void*)UART_RX_BUFFER,Size);    /*!<数据写入环形缓冲区*/
            app_event_send(EVT_UART_RX_DATA, Size);                        /*!<发送通知*/
            HAL_UARTEx_ReceiveToIdle_DMA(&huart2,(uint8_t*)UART_RX_BUFFER,64);/*!<重启UART接收(DMA NORMAL模式下)*/
        }
    }
}

/**
  * @brief  UART发送完成回调
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

    if(huart->Instance == USART2){
    
        
    
    
    
    }
}
/**
 * @brief  回调函数
 */
void app_event_handler(const app_evt_t* evt) {
    
    switch (evt->type) {
        case EVT_TEMP_READ_START:
            /*================处理片外ADC温度的读取事件==================
             *1: 启动一次SPI读取；
             *2：如果MOSFET过温，抛出EVT_TEMP_OVERLIMIT_FAULT事件(不推荐,存在FIFO排队问题)
             *     或直接处理(推荐)
             *      或(如果使用SPI+DMA/IT)在DMA中断中直接判断ADC原值后直接处理
             *3：根据最高温度处理PID更新PWM(如果风扇需要调速)
            =============================================================*/
            
            
            break;

        case EVT_TEMP_OVERLIMIT_FAULT:// 处理MOSFET过温事件
                            
                            
            break;
                            
        case EVT_VSWR_FAULT:// 处理功放反射过大事件
                            
                            
            break;
                    
        case EVT_CURRENT_IMBALANCE_FAULT:// 处理电流失衡事件
                            
                    
            break;
                    
        case EVT_UART_RX_DATA:// 处理串口数据接收事件，param 可以是接收到的字节指针
            
            if(evt->param > 128){
                
                //数据过长，清空缓冲区并忽略
                lwrb_skip(&rb_uart, evt->param);
                
                break;
                
            }
                
            uint8_t UART_FRAME[128];//接收到的数据帧
            lwrb_read(&rb_uart,(uint8_t*)UART_FRAME,evt->param);//读取数据
            UART_FRAME[evt->param] = 0;//添加字符串结束符 \0
            //frame_handler...        
            parse_ascii_command((char*)UART_FRAME, evt->param);        
            break;                
                
        case EVT_ADC_SAMPLE_COMPLETE:// 处理片上ADC事件，param 可以是接收到的字节指针
                            
                    
            break;
                    
        case EVT_SYS_INIT_DONE://处理开机事件
                            
                    
            break;
        
        case EVT_DEBUG:
            
            led1_toggle();
//            Relay_Set_Combination(RELAY_ALL_OFF);//继电器全
//            HAL_Delay(500);
//            Relay_Set_Combination(RELAY_ALL_ON);//继电器全
//            HAL_Delay(500);
            RF_Matching_Optimize();//遍历所有继电器


//            SIG_ON();
//            HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_SET);
//            HAL_Delay(50);
//            HAL_GPIO_WritePin(GPIOB, USER_IO3_Pin, GPIO_PIN_RESET);
//            SIG_OFF();
//            HAL_Delay(50);
            break;
         case EVT_GET_TEMP:
//             led2_toggle();
//             Get_RF_temp();
//             Get_MOS_temp();
         case EVT_KEY:
             led2_toggle();
             Cool_Pulse_ctr(5);
         
                    
        default:
            
            break;
    }
}