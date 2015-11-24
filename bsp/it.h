#ifndef IT_H_
#define IT_H_

extern TIM_HandleTypeDef Tim4Handle;

void SysTick_Handler(void);
void TIM4_IRQHandler(void);
//void SPI2_IRQHandler(void);
//void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef*);



#endif /* IT_H_ */
