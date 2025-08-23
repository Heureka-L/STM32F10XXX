#include "stm32f10x.h"

void IC_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//GPIOA

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStucture);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3_Enable
    TIM_InternalClockConfig(TIM3);//TIM3_InternalClock

    TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
    TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStructure.TIM_Period = 65536 - 1;
    TimeBase_InitStructure.TIM_Prescaler = 72000000/1000000 - 1; // 1MHz
    TimeBase_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TimeBase_InitStructure);

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);//IC_Initial

    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//输入源选择
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//从模式配置

    TIM_Cmd(TIM3, ENABLE);
}


uint16_t IC_GeiFreq(void){

    return 1000000/(TIM_GetCapture1(TIM3)+1);

}   
