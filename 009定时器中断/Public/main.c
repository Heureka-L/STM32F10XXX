#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Timer.h"

int main(void){
	Timer_Init();
	LED_Init();
	while(1){
		LED_ShowNum(Timer_counter());
	}
}
