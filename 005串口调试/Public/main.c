#include "stm32f10x.h"
#include "Delay.h"
#include "UartDebug.h"

int main(void) {
    // 初始化串口（波特率9600）
    UART1_Init_(9600);
    uart_sendstring("System Ready!\r\n");

    while (1) {
        uart_sendstring("hello");
		Delay_ms(1000);
    }
}
