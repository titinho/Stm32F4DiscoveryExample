/*
 * bsp.h
 *
 *  Created on: 2014 okt. 9
 *      Author: titus_000
 */

#ifndef BSP_H_
#define BSP_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "diag/Trace.h"

#define LED_GREEN (unsigned short)1<<12
#define LED_ORANGE (unsigned short)1<<13
#define LED_RED (unsigned short)1<<14
#define LED_BLUE (unsigned short)1<<15

#define LED_ALL (unsigned short)0xf000

#define LED_PORT GPIOD

void LedInit(unsigned short ledPos);
void LedOn (unsigned short ledPos);
void LedOff (unsigned short ledPos);
void LedSet (unsigned short ledPos, unsigned short value);
void LedToggle(unsigned short ledPos);

void Tim4Init();
void Spi2Init();
void GpioPushButtonInit();
void GpioSpi2Init();

extern unsigned char LedEnable;
extern TIM_HandleTypeDef Tim4Handle;
#endif /* BSP_H_ */
