#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdlib.h"
#include "LED.h"
#include "R_Encoder.h"

uint16_t EncoderNum = 0;

int main(void){
	LED_Init();
	R_EncoderInit();
	while(1){
		EncoderNum += R_EncoderGet();
		LED_ShowNum(EncoderNum);
	}
}
