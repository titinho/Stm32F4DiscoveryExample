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
}

void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&Spi2Handle);
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	LedToggle(LED_RED);
	char data[3] = { 0x12, 0x34 , 0x56};
	HAL_SPI_Receive(&Spi2Handle,(char*)&data,2,100);
	HAL_SPI_Transmit(&Spi2Handle,(char*)&data,2,100);
	__HAL_TIM_CLEAR_FLAG(&Tim4Handle,TIM_FLAG_UPDATE);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_0)
	{
		LedToggle(LED_GREEN);
	}
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_0);
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* spiHandle)
{
	for(int i=0;i<6;i++)
	{
		LedToggle(LED_ORANGE);
		HAL_Delay(100);
	}
}
