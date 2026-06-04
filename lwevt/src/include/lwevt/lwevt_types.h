/**
 * \file            lwevt_types_template.h
 * \brief           LwEVT application types
 */

/*
 * Copyright (c) 2024 Tilen MAJERLE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of LwEVT - Lightweight event manager.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         v1.0.0
 */

/* Rename this file to "lwevt_opts.h" for your application and do not use include guard macros */

/*
 * Define your different event types with 2 macros
 *
 * Basic definition - event type w/o possibility for data
 * 
 * LWEVT_TYPE_BASIC(APP_EVT_BASIC_1)
 * 
 * Extended definition - event type w/ possibility for data
 * 
 * LWEVT_TYPE_BASIC(APP_EVT_EXT_W_DATA_1, struct { uint32_t my_par1; uint32_t my_par2; } ext_w_data;)
 */
/* Define basic types */

LWEVT_TYPE_BASIC(EVT_TEMP_READ_START)					//温度读取请求事件
LWEVT_TYPE_BASIC(EVT_TEMP_OVERLIMIT_FAULT)		//温度过大事件
LWEVT_TYPE_BASIC(EVT_VSWR_FAULT)							//反射功率过大错误
LWEVT_TYPE_BASIC(EVT_CURRENT_IMBALANCE_FAULT)	//电流不平衡错误
LWEVT_TYPE_BASIC(EVT_UART_RX_DATA)						//串口收到数据
LWEVT_TYPE_BASIC(EVT_ADC_SAMPLE_COMPLETE)			//ADC转换完成
LWEVT_TYPE_BASIC(EVT_SYS_INIT_DONE)						//开机事件
/*
	注意此处无需任何include,也无需#ifndef XXX_H #define XXX_H
	Keil原因,此处报错无需处理
*/

/* Define extended types */
//	LWEVT_TYPE_EXT(EVT_ADC_DATA_READY, struct {
//  lwrb_t* ptr_rb; 		// 指向处理好的ADC数据
//  uint32_t  data_len; // 数据长度
//} adc_data)

