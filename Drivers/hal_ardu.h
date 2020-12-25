/*
 * hal_ardu.h
 *
 *  Created on: 14 дек. 2020 г.
 *      Author: me
 */

#ifndef HAL_ARDU_H_
#define HAL_ARDU_H_

#include "stm32f1xx_hal.h"

#include <stdbool.h>

void delayMicroseconds(int);

void digitalWrite(char n, bool PinState);
void pinMode(char pin, /*GPIO_InitTypeDef**/int value);

#endif /* HAL_ARDU_H_ */
