#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct 
{
	GPIO_TypeDef * GPIO;
	char GPIO_Pin; 	// 0 - 15
	char GPIO_Conf; //below
} MyGPIO_Struct_TypeDef;

//Page 160
#define In_Floating 			0x4//0100
#define In_PullDown 			0x8//1000
#define In_PullUp 				0x8//1000
#define In_Analog 				0x0//0000
#define Out_PushPull 			0x1//00-01  Max. output speed (01: 10 MHz | 10:  2 MHz | 11: 50 MHz)
#define Out_OpenDrain			0x5//01-01	Max. output speed (01: 10 MHz | 10:  2 MHz | 11: 50 MHz)
#define AltOut_PushPull		0xA//10-01	Max. output speed (01: 10 MHz | 10:  2 MHz | 11: 50 MHz) configurado a 2MHz
#define AltOut_OpenDrain	0xD//11-01	Max. output speed (01: 10 MHz | 10:  2 MHz | 11: 50 MHz)

void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr);
int MyGPIO_Read (GPIO_TypeDef * GPIO, char GPIO_pin); //0 or different
void MyGPIO_Set (GPIO_TypeDef * GPIO, char GPIO_pin);
void MyGPIO_Reset (GPIO_TypeDef * GPIO, char GPIO_pin);
void MyGPIO_Toggle (GPIO_TypeDef * GPIO, char GPIO_pin);

#endif
