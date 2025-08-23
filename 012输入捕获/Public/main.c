#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "InputCampture.h"
int main(void){
	PWM_Init();
	IC_Init();
	PWM_SetFreq(1000);
	PWM_SetDuty(50);
	while(1){
		IC_GeiFreq();
	}
}
