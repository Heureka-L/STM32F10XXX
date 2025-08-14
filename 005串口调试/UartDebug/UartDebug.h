#ifndef __UARTDEBUG_H
#define __UARTDEBUG_H

#include "stm32f10x.h"
#include <stdint.h>

// 函数声明
void UART1_Init_(uint32_t baudrate);          // 初始化UART1（波特率可配置）
void uart_sendchar(char c);                  // 发送单个字符
void uart_sendstring(const char *str);       // 发送字符串
void uart_send_nu(int32_t num, uint8_t base); // 发送数字（base=10:十进制, base=16:十六进制）
void uart_send_array(uint8_t *arr, uint16_t len); // 发送字节数组

// 中断相关（可选）
void UART1_IRQHandler(void);                 // 串口1中断服务函数

#endif
