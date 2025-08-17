#include "stm32f10x.h"                  // Device header
#include "Timer.h"

void LED2_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);
}

void Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);					//则设置PA1引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);					//则设置PA1引脚为低电平
	}
}

 int main(void){

	uint16_t temp = 0;
	LED2_Init();
	Timer_Init();
	while(1){

		temp = Timer_counter();

		if(Timer_counter() > temp){
			Turn();
		}
		
	}
}
