#include "hal_ardu.h"


void digitalWrite(char n, bool PinState){
		switch (n){
		case 29:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8, (GPIO_PinState) PinState);
			break;
		case 25:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12, (GPIO_PinState) PinState);
			break;
		default:
//#error !
			break;
		}
 }


void pinMode(char pin, /*GPIO_InitTypeDef**/int value){
//		switch (n){
//		case 29:
//			HAL_GPIO_Init(GPIOA,GPIO_PIN_8, value);
//			break;
//		default:
//	#error !!! add pin
//		}
 }

void delayMicroseconds(int n){
	int m=n*64;
	while (m) m-=1;
}
