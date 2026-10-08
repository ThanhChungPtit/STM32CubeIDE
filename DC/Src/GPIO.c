#include "GPIO.h"
void GPIO_Config(volatile GPIO_TypeDef * GPIOx, uint16_t Pin, uint16_t Mode) {
	uint16_t config =0 ;
	uint8_t is_pullup=0 ;
	uint8_t is_pulldown=0 ;

	switch(Mode) {
	  case GPIO_MODE_INPUT_ANALOG:
		  config = (0x0 << 2) | (0x0 << 0);
		  break ;
	  case GPIO_MODE_INPUT_FLOATING:
		  config = (0x1<<2) | (0x0<<0) ;
		  break ;
	  case GPIO_MODE_INPUT_PULLUP:
		  config = (0x2<<2) | (0x0<<0);
		  is_pullup = 1 ;
		  break ;
	  case GPIO_MODE_INPUT_PULLDOWN:
		  config = (0x2<<2) | (0x0<<0) ;
		  is_pulldown =1 ;
		  break ;
	  case GPIO_MODE_OUTPUT_PP:
	      config = (0x0 << 2) | (0x3 << 0); // Output 50MHz
	      break;
	  case GPIO_MODE_OUTPUT_OD:
	       config = (0x1 << 2) | (0x3 << 0);
	       break;
	  case AF_MODE_OUTPUT_PP:
	       config = (0x2 << 2) | (0x3 << 0);
	       break;
	case AF_MODE_OUTPUT_OD:
	       config = (0x3 << 2) | (0x3 << 0);
	       break;
	}

	for(uint16_t i=0 ;  i<16 ; i++ ){
		if(Pin & 1<<i) {
			if(i<8) {
				GPIOx->CRL &=~ (0xF<<(i*4)) ;
				GPIOx->CRL |= (config<<(i*4)) ;
			}
			else {
				GPIOx->CRH &=~ ( 0xF << ((i-8)*4) ) ;
				GPIOx->CRH |= ( config<< ((i-8)*4) ) ;
			}
			if(is_pullup) {
				GPIOx->ODR |= (1<<i) ;
			}
			else {
				GPIOx->ODR &=~ (1<<i) ;
			}
		}
	}
}
void GPIO_WritePin(volatile GPIO_TypeDef * GPIOx, uint16_t Pin, uint8_t state) {
	if(state) {
		GPIOx->BSRR = Pin ;
	}
	else {
		GPIOx->BRR = Pin ;
	}
}
uint8_t GPIO_ReadPin(volatile GPIO_TypeDef * GPIOx, uint16_t Pin) {
	return ((GPIOx->IDR & Pin)? 1:0) ;
}
