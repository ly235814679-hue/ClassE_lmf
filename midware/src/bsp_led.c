/*led相关函数*/
#include "bsp_led.h"

void led1_on(){
    
    LED1_GPIO_Port->BSRR = (uint32_t)LED1_Pin << 16u;/*<设置为低电平>*/
}
void led1_off(){

    LED1_GPIO_Port->BSRR = LED1_Pin;/*<设置为高电平>*/

}
void led1_toggle(){

    LED1_GPIO_Port->ODR ^= LED1_Pin;/*<翻转LED>*/
}
void led2_on(){

    LED2_GPIO_Port->BSRR = (uint32_t)LED2_Pin << 16u;/*<设置为低电平>*/

}
void led2_off(){

    LED2_GPIO_Port->BSRR = LED2_Pin;/*<设置为高电平>*/

}
void led2_toggle(){

    LED2_GPIO_Port->ODR ^= LED2_Pin;/*<翻转LED>*/

}