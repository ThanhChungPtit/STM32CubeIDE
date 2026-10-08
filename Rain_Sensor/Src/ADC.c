#include "ADC.h"

void ADC01_CH0_Init(void){
	//select sample cycles
	ADC01_SMPR2 &= ~(uint32_t)(0x7 << 0);//reset channel 0
	ADC01_SMPR2 |= (1 << 1);// select sample time=13.5 for channel 0
	ADC01_SQR3 = 0;
	ADC01_CR2 |= (1 << 1);//select continous conversion mode
	//enable ADC and to start conversion
	ADC01_CR2 |= (1 << 0); //ADON-Wake up ADC to it exit Power-Down state
	for(volatile uint32_t i = 0; i < 2000; i++) {
	        __asm("NOP");
	    }
	ADC01_CR2 |= (1 << 0);//Really Start conversion
	//calibration
	ADC01_CR2 |= (1 << 3);//Initialize calibration register
	while(ADC01_CR2 & (1 << 3)){}//waiting for RSTCAL=0
	ADC01_CR2 |= (1 << 2);//enable calibration
	while(ADC01_CR2 & (1 << 2)){}//wait

	ADC01_CR2 |= (1 << 22);//Starts conversion of regular channels
}

uint16_t ADC01_CH0_Read(void){
	while(!(ADC01_SR & (1 << 1))){
	}
	return (uint16_t)(ADC01_DR & 0xFFFF);
}
