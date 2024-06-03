#include "../Include/MyLed.h"
#include "MyADC.h"

int current_DC;  // current duty cycle, min 0% max 100%
char direction;  // to kwon if it's going up or down the duty cycle, 1 means to raise intensity, 0 means to low intensity

void MyLed_init(int T){
	//Calculate time to interruption to change duty cycle (40 times per period)	
	float time_interruption = T/40.0;
	int psc = (72000000 * time_interruption)/(32000+1) - 1; // arr = 32000 
	
	//GPIOStructs for config led and potentiometer signal
	MyGPIO_Struct_TypeDef  gpio_conf;
	MyGPIO_Struct_TypeDef  gpio_pot;
	
	//Creation of GPIOStruct which defines the port to use where the led should be connected
	gpio_conf.GPIO = Port_Led;
	gpio_conf.GPIO_Pin = Pin_Led;
	gpio_conf.GPIO_Conf = AltOut_PushPull; // because it is PWM
	
	//Creation of GPIOStruct which defines the ports to receive the signal of the potenciometer
	gpio_pot.GPIO = Port_Potentiometer;
	gpio_pot.GPIO_Pin = Pin_Potentiometer;
	gpio_pot.GPIO_Conf = In_Analog; // because the entry changes between 0 and 3.3 V
	
	//GPIO configuration with the above specifications 
	MyGPIO_Init(&gpio_conf);  // send the total struct
	MyGPIO_Init(&gpio_pot);
	
	//Frequency configuration for timer with arr and psc and init timer
	MyTimer_Base_Init(Tim_PWM, 511, 1097);
	MyTimer_Base_Start(Tim_PWM);

	//Duty cycle set to zero to start with led off
	current_DC = 0;
	MyTimer_PWM_config(Tim_PWM, current_DC);
	MyTimer_PWM_init(Tim_PWM, 1);
	direction = 1;
	
	//Config interruption to change duty cycle of led
	MyTimer_Base_Init(Tim_Interruption,32000,psc);
	MyTimer_Base_Start(Tim_Interruption);
	MyTimer_ActiveIT(Tim_Interruption, 1,MyLed_setDC);   // every X seconds with priority 1 we execute MyLed_setDC  ( change the intensity of LED)
	
	start_ADC();  // 
	do
	{
		uint16_t value = ADC_Value();  // value read from the IN_ANALOG
		int new_period = 1 + (value*9/4095);  // time goes between 1 and 10 sec
		MyLed_changePeriod(new_period);
	}
	while(1);  // infinite loop  -> always getting a value to change the period 
}

// function to increase or to decrease the dutycycle 5 by 5 (5%..10%..15%)
// it should be called 20 times in a period
void MyLed_setDC(){  // min 0% max 100%
	if(current_DC >= 100){
		direction = 0;
	}
	else if(current_DC <= 0){
		direction = 1;
	}
	
	if(direction==1){
		current_DC = current_DC + 5; // 1 means to raise intensity
	}
	else if(direction==0){
		current_DC = current_DC - 5; //  0 means to low intensity
	}
	MyTimer_PWM_config(Tim_PWM, current_DC);
}

void MyLed_changePeriod(int T){
	float time_interruption = T/40.0;  // 
	int psc = (72000000 * time_interruption)/(32000+1) - 1;
	
	//Config interruption to change duty cycle of led
	MyTimer_Base_Init(Tim_Interruption,32000,psc);
	//MyTimer_Base_Start(Tim_Interruption);
	//MyTimer_ActiveIT(Tim_Interruption, 1,MyLed_setDC);
}



