#include "bsp_lwevt.h"
#include <stdio.h>

/* * -------------------------------------------------------------------------
 * 私有函数：事件处理逻辑
 * -------------------------------------------------------------------------
 * 注册到lwevt，当 lwevt_dispatch被调用时执行。
 */
static void Prv_System_EventHandler(lwevt_t* evt) {
	
    switch (evt->type) {

        case EVT_TEMP_READ_START:{

            break;
				}
        case EVT_TEMP_OVERLIMIT_FAULT:{

            break;
				}
        case EVT_VSWR_FAULT: {

            break;
        }
				case EVT_CURRENT_IMBALANCE_FAULT: {

            break;
        }
				case EVT_UART_RX_DATA: {

            break;
        }
				case EVT_ADC_SAMPLE_COMPLETE: {
				
						break;			
				}

        default:
					
            break;
    }
}

/* * -------------------------------------------------------------------------
 * 初始化
 * *-------------------------------------------------------------------------
 */
void BSP_LwEVT_Service_Init(void) {

    /* 1. 初始化 lwevt  */
    lwevt_init();

    /* 2. 注册静态回调函数 */
    lwevt_register(Prv_System_EventHandler);

		/* 3. 分发1个初开机事件 */
    lwevt_dispatch(EVT_SYS_INIT_DONE);
	
}