#ifndef IT_H_
#define IT_H_

extern TIM_HandleTypeDef Tim4Handle;

void SysTick_Handler(void);
void TIM4_IRQHandler(void);
void SPI2_IRQHandler(void);
void EXTI0_IRQHandler(void);

#endif /* IT_H_ */
