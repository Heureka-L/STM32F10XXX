#include "stm32f10x.h"

void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_2 | GPIO_Pin_3);
}

void LED_Set(uint8_t chooseLED,uint8_t state){
    if(chooseLED == 1){
        if(state == 1){
            GPIO_SetBits(GPIOA,GPIO_Pin_2);
        }else{
            GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        }
    }else if(chooseLED == 2){
        if(state == 1){
            GPIO_SetBits(GPIOA,GPIO_Pin_3);
        }else{
            GPIO_ResetBits(GPIOA,GPIO_Pin_3);
        }
    }
}

void LED_Turn(uint8_t chooseLED){
    if(chooseLED == 1){
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0){
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
    }else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    }
    }
    if(chooseLED == 2){
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_3)==0){
        GPIO_SetBits(GPIOA,GPIO_Pin_3);
    }else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_3);
    }
    }    
}
