#include "GPIO.h"
void GPIO_Config(volatile GPIO_Typedef* GPIOx,uint16_t GPIO_Pin,uint16_t Mode) {
	uint32_t position=0 ;
	uint32_t config=0 ;
	for(position=0 ; position<16 ; position++) {
		if(GPIO_Pin & (1<<position)) {
			//reset
			if(position<8) {
				GPIOx->CRL &=~(0xF<<(position*4)) ;

			}
			else {
				GPIOx->CRH &=~(0xF<<(position-8)*4) ;
			}
			switch(Mode) {
				case GPIO_MODE_OUTPUT_PP:
					config = (0x03<<0) | (0x00 <<2) ;
				    break ;
				case GPIO_MODE_OUTPUT_OD:
					config = (0x03<<0) | (0x01<<2) ;
				    break ;
				case GPIO_MODE_AF_PP:
					config = (0x03<<0) | (0x02<<2) ;
				    break ;
				case GPIO_MODE_AF_OD:
					config = (0x03<<0) |(0x03<<2) ;
				    break ;
				case GPIO_MODE_INPUT_ANALOG:
					config = (0x00<<2) ;
				    break ;
				case GPIO_MODE_INPUT_FLOATING:
					config = (0x01<<2) ;
				    break ;
				case GPIO_MODE_INPUT_PU:
					config =(0x02<<2) ;
				    GPIOx->ODR |=(1<<position) ;
				    break ;
				case GPIO_MODE_INPUT_PD:
					config=(0x02<<2) ;
				    GPIOx->ODR &=~(1<<position) ;
				    break ;
			}
			if(Mode==GPIO_MODE_INPUT_ANALOG || Mode==GPIO_MODE_INPUT_FLOATING || Mode==GPIO_MODE_INPUT_PD || Mode==GPIO_MODE_INPUT_PU) {
				config |=(0x00<<0) ;
			}

			//set
			if(position<8) {
				GPIOx->CRL |=(config<<(position*4)) ;
			}
			else {
				GPIOx->CRH |=(config<<(position-8)*4) ;
			}
		}
	}
}
void GPIO_WritePin(volatile GPIO_Typedef* GPIOx,uint16_t GPIO_Pin,uint8_t state) {
	if(state) {
		GPIOx->BSRR = GPIO_Pin ;
	}
	else {
		GPIOx->BRR = GPIO_Pin ;
	}
}
uint8_t GPIO_ReadPin(volatile GPIO_Typedef* GPIOx, uint16_t GPIO_Pin) {
	return ((GPIOx->IDR & GPIO_Pin)? 1:0) ;
}
