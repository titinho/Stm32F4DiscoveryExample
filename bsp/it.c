/*
 * it.c
 *
 *  Created on: 2014 okt. 9
 *      Author: titus_000
 */

#include "bsp.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


