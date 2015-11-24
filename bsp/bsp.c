/*
 * bsp.c
 *
 *  Created on: 2014 okt. 9
 *      Author: titus_000
 */

#include "bsp.h"

unsigned char LedEnable;
TIM_HandleTypeDef Tim4Handle;
SPI_HandleTypeDef Spi2Handle;

void HAL_MspInit(void)
{
	LedInit(LED_ALL);
	Tim4Init();
	SpiInit();
	NvicInit();
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

void Tim4Init()
{
	__TIM4_CLK_ENABLE();

	Tim4Handle.Instance = TIM4;
	Tim4Handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	Tim4Handle.Init.CounterMode=TIM_COUNTERMODE_UP;
	Tim4Handle.Init.Prescaler=41999;
	Tim4Handle.Init.Period=999;

	//?????
	HAL_TIM_Base_Init(&Tim4Handle);
}

void NvicInit()
{
	HAL_NVIC_SetPriority(TIM4_IRQn,0,1);
	HAL_NVIC_SetPriority(SPI2_IRQn,0,2);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
	HAL_TIM_Base_Start_IT(&Tim4Handle);
}

/*
 * SPI mode 3
 */
void SpiInit()
{
	__SPI2_CLK_ENABLE();

	Spi2Handle.Instance               = SPI2;
	Spi2Handle.Init.BaudRatePrescaler = 256;
	Spi2Handle.Init.Direction         = SPI_DIRECTION_2LINES;
	Spi2Handle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	Spi2Handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	Spi2Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
	Spi2Handle.Init.CRCPolynomial     = 7;
	Spi2Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
	Spi2Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	Spi2Handle.Init.NSS               = SPI_NSS_SOFT;
	Spi2Handle.Init.TIMode            = SPI_TIMODE_DISABLED;
	Spi2Handle.Init.Mode              = SPI_MODE_SLAVE;

	HAL_SPI_Init(&Spi2Handle);
}
