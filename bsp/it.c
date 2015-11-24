#include "bsp.h"
#include "it.h"

extern TIM_HandleTypeDef Tim4Handle;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&Tim4Handle);
	LedToogle(LED_RED);
}


