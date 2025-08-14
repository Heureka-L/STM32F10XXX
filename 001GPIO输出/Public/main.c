#include "stm32f10x.h"
#include "Delay.h"

int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	uint16_t num = 0x0001;
    while(1){
		GPIO_Write(GPIOA,~num); //0000 0000 0000 0000
		Delay_ms(2000);
		num= num<<1;
		if(num>=0x0040){ 
			num = 0x0001;
		}
  }
}
