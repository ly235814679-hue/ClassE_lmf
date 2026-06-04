#ifndef __COMMAND_PARSER_H
#define __COMMAND_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <main.h>
#include <stm32f1xx_hal.h>
#include <stdint.h>
#include <stdarg.h>  // 用于 va_list, va_start 等
#include <string.h>  // 用于 strlen
/* =========================================================================
 * 函数声明
 * ========================================================================= */


/**
 * @brief  解析上位机发送的 ASCII 指令
 * @note   在调用前请确保 cmd_str 以 '\0' 结尾
 * @param  cmd_str: 指令字符串指针
 * @param  len:     指令长度
 */
void parse_ascii_command(char* cmd_str, uint16_t len);


/**
 * @brief  格式化发送串口回复 (类似 printf)
 * @note   该函数具体实现在 usart.c 或 command_parser.c 中
 * @param  format: 格式化字符串
 * @param  ...:    可变参数
 */
void UART_Send_Reply(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __COMMAND_PARSER_H */