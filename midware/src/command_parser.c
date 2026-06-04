#include "command_parser.h"
#include <string.h>
#include <stdio.h>
#include "rf_matching.h"
/*
*    1. 协议帧格式 (Frame Format)
*        每一条指令都以固定字符开头和结尾，以便识别完整的控制帧。
*
*        起始符 (STX): $ (ASCII 0x24)
*
*        结束符 (ETX): \r\n (回车换行, ASCII 0x0D 0x0A)
*
*        分隔符: , (用于区分指令和参数)
*    2. 指令集定义 (Instruction Set)
*        
*        ===========================A. 控制类指令 (Host to Device)=================================
*   ==========================================================================================
*        |        序号                    功能说明                    指令格式                        示例                             |
*        |        1                            信号源控制                $RF,<STATE>                    $RF,ON (开启), $RF,OFF (关闭)    |
*        |        2                            电源控制                    $PWR,<STATE>                $PWR,ON (开启), $PWR,OFF (关闭)  |
*        |        3                            开启调谐                    $TUNE,START                    $TUNE,START                      |
*        |        4                            读取功率反射            $READ,SWR                        $READ,SWR                        |
*        |        5                            启动1次治疗                $TREAT,START                $TREAT,START                     |
*   ==========================================================================================
*
*        ===========================B. 系统回复格式 (Device to Host)=================================
*   ============================================================================================
*        |        回复内容            格式                                                            说明                                              |
*        |        执行成功            OK,<CMD>                                                    如 OK，RF 表示信号源操作成功                   |
*        |        执行失败            FAIL,<CMD>                                                如 FAIL,TUNE,TIMEOUT (调谐超时失败)        |
*        |        数据返回            DATA,<TYPE>,<VAL1>,<VAL2>                    返回具体数值                                 |
*        |        非法指令            ERR,INVALID_CMD                                        收到无法解析的代码                                        |
*   ============================================================================================
* 3. 交互流程示例
*        
*        ===========================场景 1：开启电源并启动信号源================================
*
*
*                发送: $PWR,ON\r\n
*                回复: OK,PWR\r\n
*    
*                发送: $RF,ON\r\n
*                回复: OK,RF\r\n
*
*        ===========================场景 2：读取功率与反射情况==================================
*
*                发送: $READ,SWR\r\n
*                回复: DATA,SWR,PFF:100W,PREF:2W\r\n (注：PFF 为前向功率，PREF 为反射功率)
*
*        ===========================场景 3：启动治疗过程========================================
*
*                发送: $TREAT,START\r\n
*                回复: OK,TREAT\r\n (系统开始工作)
*
*        ===========================场景 4：过程中发送非法指令 =================================
*                
*                发送: $FUCKU\r\n
*                回复: ERR,INVALID_CMD\r\n
*/
extern UART_HandleTypeDef huart2;
/**
 * @brief  发送格式化串口回复 (阻塞式)
 * @note   使用 HAL_UART_Transmit，阻塞 CPU 直到发送完成
 * @param  format: 格式化字符串，用法同 printf
 * @param  ...: 可变参数
 */
void UART_Send_Reply(const char* format, ...) 
{
    // 定义发送缓冲区
    // 64字节够了
    char tx_buffer[64];

    // --- 1. 处理可变参数 ---
    va_list args;
    
    // 初始化参数列表
    va_start(args, format);
    
    // 使用 vsnprintf 将格式化数据写入缓冲区
    int len = vsnprintf(tx_buffer, sizeof(tx_buffer), format, args);
    
    // 清理参数列表
    va_end(args);

    // --- 2. 发送数据 ---
    // 只有当成功格式化了数据才发送
    if (len > 0) {
        // 参数说明：
        // &huart2: 串口句柄
        // (uint8_t*)tx_buffer: 强制转换为 HAL 库需要的类型
        // len: 发送数据的长度
        // 100: 超时时间 100ms。如果串口卡死，100ms后函数会强行返回，防止死机
        HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, len, 100);
    }
}
/**
 * @brief 解析ASCII指令
 * @param cmd_str: 接收到的字符串 (必须以 \0 结尾)
 * @param len: 长度
 */
void parse_ascii_command(char* cmd_str, uint16_t len) {
    // 1. 简单校验：必须以 $ 开头
    if (cmd_str[0] != '$') {
        UART_Send_Reply("ERR,INVALID_HEADER\r\n");
        return;
    }

    // 移除可能存在的 \r 或 \n，方便后续比较
    char* end = strpbrk(cmd_str, "\r\n");
    if (end) *end = '\0';

    // 2. 指令匹配
    
    // === CMD 1: 信号源控制 ($RF,ON / $RF,OFF) ===
    if (strncmp(cmd_str, "$RF,", 4) == 0) {
        char* param = cmd_str + 4; // 跳过 "$RF,"
        if (strcmp(param, "ON") == 0) {
                    
            // TODO:打开射频
            // RF_Source_Enable(true);
            UART_Send_Reply("OK,RF\r\n");
        } 
        else if (strcmp(param, "OFF") == 0) {
            // TODO: 关闭射频
            // RF_Source_Enable(false);
            UART_Send_Reply("OK,RF\r\n");
        } 
        else {
            UART_Send_Reply("FAIL,RF,PARAM_ERR\r\n");
        }
    }
    
    // === CMD 2: 电源控制 ($PWR,ON / $PWR,OFF) ===
    else if (strncmp(cmd_str, "$PWR,", 5) == 0) {
        char* param = cmd_str + 5;
        if (strcmp(param, "ON") == 0) {
            // TODO: 打开主电源 (Relay/Buck)
            UART_Send_Reply("OK,PWR\r\n");
        } 
        else if (strcmp(param, "OFF") == 0) {
            // TODO: 关闭主电源
            UART_Send_Reply("OK,PWR\r\n");
        } 
        else {
            UART_Send_Reply("FAIL,PWR,PARAM_ERR\r\n");
        }
    }

    // === CMD 3: 开启调谐 ($TUNE,START) ===
    else if (strcmp(cmd_str, "$TUNE,START") == 0) {
        // TODO: 启动自动阻抗匹配状态机
        // Tune_StateMachine_Start();
        UART_Send_Reply("OK,TUNE\r\n"); 
        // 注意：调谐通常需要时间，可以在调谐完成后再发一个异步消息，或者先回OK表示收到了
    }

    // === CMD 4: 读取功率反射 ($READ,SWR) ===
    else if (strcmp(cmd_str, "$READ,SWR") == 0) {
        // TODO: 获取实时值
        float fwd_pwr = 100.5f; // 示例值
        float ref_pwr = 2.1f;   // 示例值
        
        // 按照协议格式回复: DATA,SWR,PFF:100W,PREF:2W
        UART_Send_Reply("DATA,SWR,PFF:%.1f,PREF:%.1f\r\n", fwd_pwr, ref_pwr);
    }

    // === CMD 5: 启动治疗 ($TREAT,START) ===
    else if (strcmp(cmd_str, "$TREAT,START") == 0) {
        // TODO: 检查是否治疗完成
        // if (Safety_Check()) {
        //     Treatment_Start();
        UART_Send_Reply("OK,TREAT\r\n");
        // } else {
        //     UART_Send_Reply("FAIL,TREAT,INTERLOCK\r\n");
        // }
    }
    
    // === 未知指令 ===
    else {
        UART_Send_Reply("ERR,UNKNOWN_CMD\r\n");
    }
}