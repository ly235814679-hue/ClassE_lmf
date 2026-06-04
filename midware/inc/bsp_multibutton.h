/**
 * @file    bsp_multibutton.h
 * @brief   按键初始化头文件
 * 
 * @details
 * 本模块提供系统所有按键的枚举定义、按键初始化和事件处理接口。
 * 支持板上按键和外接按键的统一管理，支持单击、双击、长按等事件。
 * 
 * @author  Yuan Jiawen <jw.yuan@nmed.org.cn>
 * @date    2025-12-24
 * @version v1.0.0
 * 
 * @copyright xxx
 * 
 * @note
 * 1. 按键消抖时间: 15ms
 * 2. 重复按下判定时间：300ms
 * 3. 长按判定时间：1000ms
 * 
 * @history
 * | Date       | Version | Author      | Description          |
 * |------------|---------|-------------|----------------------|
 * | 2025-12-24 | v1.0.0  | Yuan Jiawen | 初始版本             |
 */

#pragma once
#include "multi_button.h"
#include "stm32f1xx.h"
#include "main.h"
#include "tim.h"

enum Button_IDs {
    KEY_ONBOARD_ID,
    KEY_EXTERNAL_ID,
    KEY_RF8_ID
};

void bsp_multibutton_Init(void);
void BTN_ONBOARD_PRESS_DOWN_Handler(void* btn);
void BTN_EXTERNAL_PRESS_DOWN_Handler(void* btn);
void BTN_RF8_PRESS_DOWN_Handler(void* btn);

