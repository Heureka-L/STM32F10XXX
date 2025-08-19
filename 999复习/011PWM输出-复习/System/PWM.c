#include "stm32f10x.h"

void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //时基单元初始化
    TIM_TimeBaseInitTypeDef TimeBaseInitStucture;
    TIM_TimeBaseStructInit(&TimeBaseInitStucture);
    TimeBaseInitStucture.TIM_ClockDivision = TIM_CKD_DIV1;//对ck_int（输入时钟）进行分频，如果PSC与ARR寄存器都不够用了在用这个
    TimeBaseInitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStucture.TIM_Period = 100 - 1;
    TimeBaseInitStucture.TIM_Prescaler = 1440 - 1;
    TimeBaseInitStucture.TIM_RepetitionCounter = 0x00; //重复次数计数器，高级定时器专用
    TIM_TimeBaseInit(TIM2,&TimeBaseInitStucture);

    //CCR初始化
    TIM_OCInitTypeDef OC_InitStucture;
    OC_InitStucture.TIM_OCMode = TIM_OCMode_PWM1; // 小于为高电平，大于为低电平
    OC_InitStucture.TIM_OCPolarity = TIM_OCPolarity_High;
    OC_InitStucture.TIM_OutputState = TIM_OutputState_Enable;
    OC_InitStucture.TIM_Pulse = 0;
    TIM_OC1Init(TIM2,&OC_InitStucture);
    //启动定时器
    TIM_InternalClockConfig(TIM2);
    TIM_Cmd(TIM2,ENABLE);
}

void PWM_SET(uint16_t Pulse)
{
    TIM_SetCompare1(TIM2,Pulse);
}
