#include "RCC.h"

void RCC_Config() {
	RCC_CR |=(1<<16) ;
	while(!(RCC_CR & (1<<17))) ;
	FLASH_ACR |= (1<<2) ;

	RCC_CFGR &=~ ((0xF<<18) | (1<<16)) ;
	RCC_CFGR |= (1<<16) ;
	RCC_CFGR |=(6<<18) ;

	RCC_CR |=(1<<24) ;
	while(!(RCC_CR & (1<<25))) ;

	RCC_CFGR &=~(0xF<<4) ;
	RCC_CFGR &=~(7<<11) ;
	RCC_CFGR |=(4<<8) ;

	RCC_CFGR &=~(3<<0) ;
	RCC_CFGR |= (2<<0) ;
	while((RCC_CFGR & (3 << 2)) != (2 << 2));
}

void RCC_Enable_PortA(void) {
	RCC_APB2ENR |= (1<<2) ;
}
void RCC_Enable_PortB(void) {
	RCC_APB2ENR |= (1<<3) ;
}
void RCC_Enable_PortC(void) {
	RCC_APB2ENR |= (1<<4) ;
}
void RCC_Enable_AFIO(void) {
	RCC_APB2ENR |= (1<<0) ;
}
void RCC_Enable_TIM2(void) {
	RCC_APB1ENR |= (1<<0) ;
}
void RCC_Enable_TIM3(void) {
	RCC_APB1ENR |= (1<<1) ;
}
void RCC_Enable_ADC01(void) {
	RCC_APB2ENR |= (1<<9) ;
}
void RCC_Enable_UART1(void) {
	RCC_APB2ENR |= (1<<14) ;
}
void RCC_Enable_SPI01(void) {
	RCC_APB2ENR |= (1<<12) ;
}
void RCC_Enable_I2C01(void) {
	RCC_APB1ENR |= (1<<21) ;
}
