#include "stm32f10x.h"

uint16_t Timer_Count = 0;

void Timer_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
    TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStructure.TIM_Period = 10000 - 1;
    TimeBase_InitStructure.TIM_Prescaler = 7500;
    TimeBase_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TimeBase_InitStructure);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStrcture;
    NVIC_InitStrcture.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStrcture.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStrcture.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStrcture.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStrcture);

    TIM_Cmd(TIM2,ENABLE);
}

uint16_t Timer_counter(void){
    return Timer_Count;
}

void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
        Timer_Count ++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
