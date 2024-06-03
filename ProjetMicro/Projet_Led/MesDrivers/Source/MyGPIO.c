#include "../Include/myGPIO.h"

void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr){
	// Configure it (page 171): Active all the GPIO's clocks
	if(GPIOStructPtr->GPIO == GPIOA){
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if(GPIOStructPtr->GPIO == GPIOB){
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if(GPIOStructPtr->GPIO == GPIOB){
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	if (GPIOStructPtr->GPIO_Pin < 8) { //We use CRL in this case
		GPIOStructPtr->GPIO->CRL &=~ (0xF << (GPIOStructPtr->GPIO_Pin * 4) ); //Reset field
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4)); //Set field
	}else {
		GPIOStructPtr->GPIO->CRH &=~ (0xF << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Reset field
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Set field
	}
	
	// If we use Pull Up or Pull Down we have to initialize the ODR bit
	if(GPIOStructPtr->GPIO_Conf == In_PullUp){
		GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
	}else if(GPIOStructPtr -> GPIO_Conf == In_PullDown){
		GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);
	}
}

// Reads IDR of GPIO_Pin
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_pin ) {
	return GPIO->IDR & (1 << GPIO_pin); //page 172
}

// Set Bit of ODR (page 172)
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_pin ){
	GPIO->ODR |= 0x1 << GPIO_pin;
}


// Reset Bit of ODR (page 172)
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_pin ) {
	GPIO->ODR &= ~(0x1 << GPIO_pin);
}

// Toggle Bit of ODR with XOR
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_pin) {
	GPIO->ODR ^= 0x1 << GPIO_pin;
}
