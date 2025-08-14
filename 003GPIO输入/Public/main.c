#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main(void){
	uint8_t keyNum;
	LED_Init();
	KeyInit();
    while(1){
		keyNum = KeyRead();
		if(keyNum==1){
			LED_Turn(1);
		}
		if(keyNum==2){
			LED_Turn(2);
		}
	}
}
