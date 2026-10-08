#include "clock.h"

void RCC_Config() {
	RCC->CR |=(1<<16) ;//on HSE
	while(!(RCC->CR & (1 << 17)));
	FLASH_ACR |= (2 << 0);

	//PLL config
	RCC->CFGR &= ~((0xF << 18) | (1 << 16));
	RCC->CFGR |= (1<<16) ;//select HSE
	RCC->CFGR |=(6<<18) ;//PLLMul x8

	//on PLL
	RCC->CR |=(1<<24) ;
	while(!(RCC->CR & (1<<25) )) ;

	// 5. Cấu hình các bộ chia (Bus Prescalers)
	RCC->CFGR &= ~(0xF << 4);  // AHB /1 (HCLK = 64MHz)
    RCC->CFGR |= (4 << 8);     // APB1 /2 (PCLK1 = 32MHz - Max 36MHz)
    RCC->CFGR &= ~(7 << 11);   // APB2 /1 (PCLK2 = 64MHz)

	// 6. Chuyển nguồn hệ thống sang PLL
    RCC->CFGR &= ~(3 << 0);    // Xóa bit SW
	RCC->CFGR |= (2 << 0);     // Chọn PLL làm hệ thống
	while((RCC->CFGR & (3 << 2)) != (2 << 2)); // Đợi xác nhận nguồn là PLL
}

void RCC_Enable_PortA(void) {
	RCC->APB2ENR |= (1<<2) ;
}
void RCC_Enable_PortB(void) {
	RCC->APB2ENR |= (1<<3) ;
}
void RCC_Enable_PortC(void) {
	RCC->APB2ENR |= (1<<4) ;
}
void RCC_Enable_AFIO(void) {
	RCC->APB2ENR |= (1<<0) ;
}
void RCC_Enable_TIM2(void) {
	RCC->APB1ENR |= (1<<0) ;
}
void RCC_Enable_TIM3(void) {
	RCC->APB1ENR |= (1<<1) ;
}
void RCC_Enable_ADC01(void) {
	RCC->APB2ENR |= (1<<9) ;
}
void RCC_Enable_UART1(void) {
	RCC->APB2ENR |= (1<<14) ;
}
void RCC_Enable_SPI01(void) {
	RCC->APB2ENR |= (1<<12) ;
}
void RCC_Enable_I2C01(void) {
	RCC->APB1ENR |= (1<<21) ;
}
