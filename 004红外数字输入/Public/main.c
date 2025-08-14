#include "stm32f10x.h"
#include "Delay.h"

int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);

	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure2);
    while(1){
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0){
			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
		}
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
  	}
}
