/**
 * @file    bsp_multibutton.c
 * @brief   按键模块初始化实现
 * 
 * @details
 * 本模块实现按键初始化、按键事件绑定、按键触发回调。
 * 使用定时器中断进行按键扫描，主循环处理按键事件。
 * 
 * @author  Yuan Jiawem <jw.yuan@nmed.org.cn>
 * @date    2025-12-24
 * @version v1.0.0
 * 
 * @copyright Copyright (c) xxx All rights reserved.
 */

#include "bsp_multibutton.h"
#include "app_event.h"
#include "bsp_led.h"

struct Button btn_sw1,btn_sw2,btn_RF8;

/**
  * @brief  内部函数，按键IO读取实现
  * @param  button_id: 需读取的按键ID
  * @retval 0/1
  */
static uint8_t read_button_GPIO(uint8_t button_id)
{
    // you can share the GPIO read function with multiple Buttons
    switch(button_id)
    {
        case KEY_ONBOARD_ID:
            return HAL_GPIO_ReadPin(USER_BTN_GPIO_Port,USER_BTN_Pin);
        
        case KEY_EXTERNAL_ID:    
            return HAL_GPIO_ReadPin(EXT_BTN_GPIO_Port,EXT_BTN_Pin);
        
        case KEY_RF8_ID:    
            return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
        default:
            return 0;
    }
}

/**
  * @brief  按键模块初始化函数，实现IO绑定、回调函数注册和启动
  * @param  None
  * @retval None
  */
void bsp_multibutton_Init(void){

    HAL_TIM_Base_Start_IT(&htim1);
    button_init(&btn_sw1, read_button_GPIO, 0, KEY_ONBOARD_ID);
    button_init(&btn_sw2, read_button_GPIO, 0, KEY_EXTERNAL_ID);
    button_init(&btn_RF8, read_button_GPIO, 0, KEY_RF8_ID);
    
    button_attach(&btn_sw1, PRESS_DOWN,BTN_ONBOARD_PRESS_DOWN_Handler);
    button_attach(&btn_sw2, PRESS_DOWN,BTN_EXTERNAL_PRESS_DOWN_Handler);
    button_attach(&btn_RF8, PRESS_DOWN,BTN_RF8_PRESS_DOWN_Handler);
    
    button_start(&btn_sw1);
    button_start(&btn_sw2);
    button_start(&btn_RF8);

}
/**
    * @brief  板上按键按下回调
  * @param  None.
  * @retval None
  */
void BTN_ONBOARD_PRESS_DOWN_Handler(void* btn){
    led2_toggle();
    app_event_send(EVT_KEY,0);

}
/**
    * @brief  外接按键按下回调
  * @param  None.
  * @retval None
  */
void BTN_EXTERNAL_PRESS_DOWN_Handler(void* btn){

}


/**
    * @brief  外接RF8按键按下回调
  * @param  None.
  * @retval None
  */
void BTN_RF8_PRESS_DOWN_Handler(void* btn){
    led2_toggle();
    app_event_send(EVT_DEBUG,0);

}