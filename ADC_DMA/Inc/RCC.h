#ifndef __RCC_H
#define __RCC_H

#include  <stdint.h>

#define RCC_BASE 0x40021000UL
#define FLASH_ACR *((volatile uint32_t*) 0x40022000UL)

#define RCC_CR        *((volatile uint32_t*)(RCC_BASE+0x00))
#define RCC_CFGR      *((volatile uint32_t*)(RCC_BASE+0x04))
#define RCC_APB2ENR   *((volatile uint32_t*)(RCC_BASE+0x18))
#define RCC_APB1ENR   *((volatile uint32_t*)(RCC_BASE+0x1C))

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
