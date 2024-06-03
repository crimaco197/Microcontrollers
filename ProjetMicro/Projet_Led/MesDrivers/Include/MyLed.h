#ifndef MyLed_h
#define MyLed_h
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

// Constant to define the port and the pin of the led
#define Port_Led GPIOA 
#define Pin_Led 0  // PA0

#define Port_Potentiometer GPIOA
#define Pin_Potentiometer 1  // PA1

// Constant to define the timer for PWM
#define Tim_PWM TIM2
#define Channel_PWM 0

// Constant to define the interruption
#define Tim_Interruption TIM3  // changes the DutyCycle -> intensity of LED

void MyLed_init(int T);
void MyLed_setDC(void);
void MyLed_changePeriod(int T);
#endif
