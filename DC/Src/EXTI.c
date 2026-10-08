#include "EXTI.h"
#include "AFIO.h"


uint16_t Get_pin(uint16_t pin) {
	for(uint16_t i=0 ; i<16 ; i++) {
		if(pin & 1<<i) {
			return i ;
		}
	}
	return 0xFF ;
}

void EXTI_Init(volatile GPIO_TypeDef *GPIOx, uint16_t Pin,uint8_t type) {
	uint16_t port_code ;
	uint16_t pin ;

	if(GPIOx == GPIOA) {
		port_code=0 ;
	}
	else if(GPIOx == GPIOB) {
		port_code=1 ;
	}
	else {
		port_code =2 ;
	}

	pin = Get_pin(Pin) ;
	uint32_t shift = (pin%4) * 4 ;

	if(pin<4) {
		AFIO_BASE->EXTICR1 &=~(0xF<<shift) ;
		AFIO_BASE->EXTICR1 |=(port_code <<shift) ;
	}
	else if(pin>=4 & pin<=7) {
		AFIO_BASE->EXTICR2 &=~(0xF<<shift) ;
		AFIO_BASE->EXTICR2 |= (port_code<<shift) ;
	}
	else if(pin>=8 && pin<=11) {
		AFIO_BASE->EXTICR3 &=~(0xF<<shift) ;
		AFIO_BASE->EXTICR3 |= (port_code<<shift) ;
	}
	else {
		AFIO_BASE->EXTICR4 &=~(0xF<<shift) ;
		AFIO_BASE->EXTICR4 |= (port_code<<shift) ;
	}

	EXTI->IMR |= 1<<pin ;

	if(type==EXTI_RISING_MODE) {
		EXTI->RTSR |= (1<<pin) ;
		EXTI->FTSR &=~(1<<pin) ;
	}
	else if(type==EXTI_FALLING_MODE) {
		EXTI->RTSR &=~(1<<pin) ;
		EXTI->FTSR |= (1<<pin) ;
	}
	else if(type==EXTI_BOTH_MODE) {
		EXTI->FTSR |= (1<<pin) ;
		EXTI->RTSR |= (1<<pin) ;
	}
	//DEtect
	if(pin<=4) {
		NVIC_ISER0 |=(1<<(6+pin)) ;
	}
	else if(pin>4 & pin<=9) {
		NVIC_ISER0 |= (1<<23) ;
	}
	else {
		NVIC_ISER1 |= (1<<(40-32)) ;
	}
}
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
