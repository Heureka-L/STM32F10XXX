#include "uartdebug.h"
#include <stdio.h>  // 用于vsnprintf

// 本地缓冲区（用于数字格式化）
#define TX_BUF_SIZE 32
static char tx_buf[TX_BUF_SIZE];

// 初始化UART1（标准库实现）
void UART1_Init_(uint32_t baudrate) {
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // 1. 使能时钟（USART1挂载在APB2总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // 2. 配置TX(PA9)为复用推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;      // 复用推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. 配置RX(PA10)为浮空输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 4. 配置USART1参数
    USART_InitStruct.USART_BaudRate = baudrate;        // 波特率（如115200）
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);

    // 5. 使能串口接收中断（可选）
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     // 接收中断使能
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 6. 启动USART1
    USART_Cmd(USART1, ENABLE);
}

// 发送单个字符（阻塞式）
void uart_sendchar(char c) {
    USART_SendData(USART1, (uint16_t)c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送完成
}

// 发送字符串
void uart_sendstring(const char *str) {
    while (*str) {
        uart_sendchar(*str++);
    }
}

// 发送数字（支持10/16进制）
void uart_send_nu(int32_t num, uint8_t base) {
    if (base == 10) {
        snprintf(tx_buf, TX_BUF_SIZE, "%ld", num);    // 十进制格式化
    } else if (base == 16) {
        snprintf(tx_buf, TX_BUF_SIZE, "0x%lX", num); // 十六进制格式化
    }
    uart_sendstring(tx_buf); // 发送格式化后的字符串
}

// 发送原始字节数组
void uart_send_array(uint8_t *arr, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        uart_sendchar(arr[i]);
    }
}

// 中断服务函数（示例：接收回显）
void UART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART1);    // 读取数据
        uart_sendchar(data);                         // 回显（可替换为自定义逻辑）
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志
    }
}
