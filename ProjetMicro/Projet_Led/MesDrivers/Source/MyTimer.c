#include "../Include/MyTimer.h"

void (* TIM1_fct_ptr) (void);
void (* TIM2_fct_ptr) (void);
void (* TIM3_fct_ptr) (void);
void (* TIM4_fct_ptr) (void);

// Initialize TIMER
// Also required for using PWM
void MyTimer_Base_Init ( TIM_TypeDef * Timer, uint16_t arr, uint16_t psc)
{
	if(Timer==TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if(Timer==TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if(Timer==TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	else if(Timer==TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	Timer->ARR = arr;
	Timer->PSC = psc;

}

void MyTimer_ActiveIT( TIM_TypeDef * Timer , char Prio , void (*IT_function) ( void ) ) 
	{
		Timer->DIER |= TIM_DIER_UIE;
		if(Timer==TIM1){
			NVIC->ISER[0] |= (01<<27);  // active interruption
			NVIC->IP[27] |= Prio;   // set priotiry
			TIM1_fct_ptr = IT_function;
		} 
		else if(Timer==TIM2) {
			NVIC->ISER[0] |= (01<<28);
			NVIC->IP[28] |= Prio;
			TIM2_fct_ptr = IT_function;
		} 
		else if(Timer==TIM3) {
			NVIC->ISER[0] |= (01<<29);
			NVIC->IP[29] |= Prio;
			TIM3_fct_ptr = IT_function;
		} 
		else if(Timer==TIM4) {
			NVIC->ISER[0] |= (01<<30);
			NVIC->IP[30] |= Prio;
			TIM4_fct_ptr = IT_function;
		}
	}

void TIM1_IRQHandler(void)
{
	TIM1->SR &= ~(1<<0);		
	(*TIM1_fct_ptr)();
	
}
void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~(1<<0);		
	(*TIM2_fct_ptr)();
	
}
void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~(1<<0);		
	(*TIM3_fct_ptr)();
	
}
void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~(1<<0);		
	(*TIM4_fct_ptr)();
	
}

void MyTimer_PWM_init(TIM_TypeDef * Timer, char Channel)
{
	//0x06=0b110
	switch (Channel)
	{
		case 2:
			Timer->CCMR1 |= (0x06<<12);
			Timer->CCR2 |= 0x3FFF;
		case 3:
			Timer->CCMR2 |= (0x06<<4);
			Timer->CCR3 |= 0x3FFF;
		case 4:
			Timer->CCMR2 |= (0x06<<12);
			Timer->CCR4 |= 0x3FFF;
		default:
			Timer->CCMR1 |= (0x06<<4);
			Timer->CCR1 |= 0x3FFF;
		}
		Timer->CCER |= (0x1 << (Channel - 1) *4);
		
}

void MyTimer_PWM_config(TIM_TypeDef * Timer, int DutyCycle)
{
	Timer->CCR1 = (DutyCycle*Timer->ARR)/100;
}


