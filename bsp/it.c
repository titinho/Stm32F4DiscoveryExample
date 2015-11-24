#include "bsp.h"
#include "it.h"

extern TIM_HandleTypeDef Tim4Handle;
extern SPI_HandleTypeDef Spi2Handle;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&Tim4Handle);
	//LedToggle(LED_RED);
}
/*
void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&Spi2Handle);
	LedToogle(LED_BLUE);
}*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	__HAL_TIM_CLEAR_FLAG(&Tim4Handle,TIM_FLAG_UPDATE);
	LedToggle(LED_RED);
}
