#ifndef MyTimer_h
#define MyTimer_h
#include "stm32f10x.h"

#define MyTimer_Base_Start(Timer) (Timer)->CR1 |= TIM_CR1_CEN
#define MyTimer_Base_Stop(Timer) (Timer)->CR1 &= ~TIM_CR1_CEN

// TIMER
void MyTimer_Base_Init ( TIM_TypeDef * Timer, uint16_t arr, uint16_t psc) ;


// INTERRUPTIONS
void MyTimer_ActiveIT  (TIM_TypeDef * Timer , char Prio , void (*IT_function ) (void) ) ;

// PWM
void MyTimer_PWM_init(TIM_TypeDef * Timer, char Channel) ;
void MyTimer_PWM_config(TIM_TypeDef * Timer, int DutyCycle);

#endif
