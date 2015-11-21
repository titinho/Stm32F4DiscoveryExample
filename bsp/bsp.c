/*
 * bsp.c
 *
 *  Created on: 2014 okt. 9
 *      Author: titus_000
 */

#include "bsp.h"

unsigned char LedEnable;

void HAL_MspInit(void)
{
	LedInit(LED_ALL);
}
void LedInit(unsigned short ledPos)
{
	GPIO_InitTypeDef portInit;
	LedEnable = 1;

	if (!(ledPos & LED_ALL)) assert_param(ledPos);

	__GPIOD_CLK_ENABLE();

	portInit.Mode=GPIO_MODE_OUTPUT_PP;
	portInit.Pin=ledPos;
	portInit.Pull=GPIO_NOPULL;
	portInit.Speed=GPIO_SPEED_LOW;

	HAL_GPIO_Init(LED_PORT,&portInit);
}
void LedOn (unsigned short ledPos)
{
	if (!(ledPos & LED_ALL)) assert_param(ledPos);

	if(LedEnable) HAL_GPIO_WritePin(LED_PORT, ledPos, GPIO_PIN_SET);
}
void LedOff (unsigned short ledPos)
{
	if (!(ledPos & LED_ALL)) assert_param(ledPos);
	if(LedEnable) HAL_GPIO_WritePin(LED_PORT, ledPos, GPIO_PIN_RESET);
}
void LedSet (unsigned short ledPos, unsigned short value)
{
	if (!(ledPos & LED_ALL)) assert_param(ledPos);
}
void LedToogle(unsigned short ledPos)
{
	if (!(ledPos & LED_ALL)) assert_param(ledPos);

	if(LedEnable) HAL_GPIO_TogglePin(LED_PORT, ledPos);
}


