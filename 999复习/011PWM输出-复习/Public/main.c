#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Key.h"
int main(void){
	Key_Init();
	PWM_Init();
	uint16_t pulse = 0;
	uint8_t num;
	while(1){
		num = Key_GetNum();
		if(num == 1){
			pulse += 10;
		}else if(num == 2){
			pulse -= 10;
		}
		PWM_SET(pulse);
	}
}
