#include "MYADC.h"
#include "stm32f10x.h"


void start_ADC(){

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // activate ADC clock
	RCC->CFGR &= ~RCC_CFGR_ADCPRE; // configure clock frequency for being less than 16 MHz
	
	ADC1->CR2 |= ADC_CR2_ADON;      // Activate ADC
	ADC1->SQR1 |= 0;      // number of conversions (in our case is just one)
	ADC1->SMPR2 |= 0x7 << 3;  // Configure sample time for channel
	ADC1->SQR3 |= 0x1;   // Select the channel for the first conversion
	ADC1->CR1 |= ADC_CR1_EOCIE;     // Habilita la interrupción por fin de conversión (opcional)
	ADC1->CR2 |= ADC_CR2_ADON;      // Starts conversion
}


uint16_t ADC_Value()  // reads all the time
{
	// start conversion
	ADC1->CR2 |= ADC_CR2_ADON;
	
	//waiting end of conversion
	while (!(ADC1->SR & ADC_SR_EOC)) { }
	
	// return value read by ADC
	return ADC1->DR;
}
