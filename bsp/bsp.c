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
GPIO_InitTypeDef GpioPushButtonInitTypeDef;
GPIO_InitTypeDef GpioSpi2InitTypeDef;

/* Buffer used for transmission */
uint8_t aTxMasterBuffer[] = "SPI - MASTER - Transmit message";
uint8_t aTxSlaveBuffer[]  = "SPI - SLAVE - Transmit message ";
/* Buffer used for reception */
#define DATA_LENGTH 1024
uint8_t aRxBuffer[DATA_LENGTH];


void HAL_MspInit(void)
{
	LedInit(LED_ALL);
	Tim4Init();
	Spi2Init();
	GpioPushButtonInit();
	GpioSpi2Init();
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
void LedToggle(unsigned short ledPos)
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
	//Tim4Handle.Init.Period=999;
	Tim4Handle.Init.Period=1998;

	HAL_NVIC_SetPriority(TIM4_IRQn,4,0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_TIM_Base_Init(&Tim4Handle);
	HAL_TIM_Base_Start_IT(&Tim4Handle);
}

void GpioPushButtonInit()
{
	__GPIOA_CLK_ENABLE();

	GpioPushButtonInitTypeDef.Mode = GPIO_MODE_IT_FALLING;
	GpioPushButtonInitTypeDef.Pull = GPIO_NOPULL;
	GpioPushButtonInitTypeDef.Pin  = GPIO_PIN_0;

	HAL_GPIO_Init(GPIOA,&GpioPushButtonInitTypeDef);

	HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void GpioSpi2Init()
{
	__GPIOB_CLK_ENABLE();

	GpioSpi2InitTypeDef.Mode = GPIO_MODE_IT_FALLING;
	GpioSpi2InitTypeDef.Pull = GPIO_NOPULL;
	GpioSpi2InitTypeDef.Pin  = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
}

void NvicInit()
{
	//HAL_NVIC_SetPriority(TIM4_IRQn,0,1);
	//HAL_NVIC_SetPriority(SPI2_IRQn,0,2);
	//HAL_NVIC_EnableIRQ(TIM4_IRQn);
	//HAL_NVIC_EnableIRQ(SPI2_IRQn);
	//HAL_TIM_Base_Start_IT(&Tim4Handle);
}

/*
 * SPI mode 3
 */
void Spi2Init()
{
	__SPI2_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	/*
	SPIx_SCK_GPIO_CLK_ENABLE();
	SPIx_MISO_GPIO_CLK_ENABLE();
	SPIx_MOSI_GPIO_CLK_ENABLE();*/

	GpioSpi2InitTypeDef.Pin       = GPIO_PIN_13;
	GpioSpi2InitTypeDef.Mode      = GPIO_MODE_AF_PP;
	GpioSpi2InitTypeDef.Pull      = GPIO_PULLDOWN;
	GpioSpi2InitTypeDef.Speed     = GPIO_SPEED_FAST;
	GpioSpi2InitTypeDef.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GpioSpi2InitTypeDef);

	/* SPI MISO GPIO pin configuration  */
	GpioSpi2InitTypeDef.Pull      = GPIO_PULLUP;
	GpioSpi2InitTypeDef.Pin       = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOB, &GpioSpi2InitTypeDef);

	/* SPI MOSI GPIO pin configuration  */
	GpioSpi2InitTypeDef.Pin       = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOB, &GpioSpi2InitTypeDef);

	Spi2Handle.Instance               = SPI2;
	Spi2Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
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
