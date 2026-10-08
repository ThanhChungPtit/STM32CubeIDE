#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdint.h>

typedef struct {
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;
	volatile uint32_t AHBRSTR ;
	volatile uint32_t CFGR2 ;
} RCC_TypeDef;


#define FLASH_ACR 		*((volatile uint32_t *)(0x40022000UL))

#define RCC          ((volatile RCC_TypeDef *) 0x40021000UL)

void RCC_Config() ;
void RCC_Enable_PortA(void) ;
void RCC_Enable_PortB(void) ;
void RCC_Enable_PortC(void) ;
void RCC_Enable_AFIO(void) ;
void RCC_Enable_TIM2(void) ;
void RCC_Enable_TIM3(void) ;
void RCC_Enable_ADC01(void) ;
void RCC_Enable_UART1(void) ;
void RCC_Enable_SPI01(void) ;
void RCC_Enable_I2C01(void) ;




#endif
