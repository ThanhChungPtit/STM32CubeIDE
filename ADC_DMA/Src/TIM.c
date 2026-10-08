#include "TIM.h"

void TIM_Init(volatile TIM_TypeDef* TIMx,uint32_t psc) {
	TIMx->CR1 &=~ (1<<0) ;
	TIMx->CNT =0 ;
	TIMx->SR &=~ (1<<0) ;//UIF
	TIMx->PSC = psc-1 ;
	TIMx->EGR |= (1<<0) ;
}
void Delay_ms(volatile TIM_TypeDef* TIMx, uint32_t ms) {
	if (ms==0) return ;
	TIMx->ARR = ms-1 ;
	TIMx->CNT=0 ;
	TIMx->SR &=~ (1<<0) ;
	TIMx->CR1 |= (1<<0) ;
	while(!(TIMx->SR & (1 << 0))) {}
	TIMx->CR1 &=~ (1<<0) ;
	TIMx->SR &=~ (1<<0) ;
}
void Delay_us(volatile TIM_TypeDef* TIMx, uint32_t us) {
	if (us==0) return ;
	TIMx->ARR = us-1 ;
	TIMx->CNT=0 ;
	TIMx->SR &=~ (1<<0) ;
	TIMx->CR1 |= (1<<0) ;
	while(!(TIMx->SR & (1 << 0))) {}
	TIMx->CR1 &=~ (1<<0) ;
	TIMx->SR &=~ (1<<0) ;
}
void PWM_Init(volatile TIM_TypeDef* TIMx, uint32_t arr,uint16_t channel) {
	switch(channel) {
	case CHANNEL_1:
		TIMx->CCMR1 &= ~(0xFF << 0);
		TIMx->CCMR1 |= (6<<4) | (1<<3) ;
		TIMx->CCER |= (1<<0) ;
		break ;
	case CHANNEL_2:
		TIMx->CCMR1 &= ~(0xFF << 8);
		TIMx->CCMR1 |= (6<<12) | (1<<11) ;
		TIMx->CCER |= (1<<4) ;
		break ;
	case CHANNEL_3:
		TIMx->CCMR2 &= ~(0xFF << 0);
		TIMx->CCMR2 |= (6<<4) | (1<<3) ;
		TIMx->CCER |= (1<<8) ;
		break ;
	case CHANNEL_4:
		TIMx->CCMR2 &= ~(0xFF << 8);
		TIMx->CCMR2 |= (6<<12) | (1<<11) ;
		TIMx->CCER |= (1<<12) ;
		break ;
	}
	TIMx->ARR= arr-1 ;
	TIMx->CR1 |= (1<<7) ;
	TIMx->EGR |=(1<<0) ;//generate update event
	TIMx->CR1 |=(1<<0) ; //enable counter


}
void Set_Duty(uint32_t ccr,volatile TIM_TypeDef* TIMx, uint16_t channel) {
	switch(channel) {
	    case CHANNEL_1: TIMx->CCR1 = ccr; break;
	    case CHANNEL_2: TIMx->CCR2 = ccr; break;
	    case CHANNEL_3: TIMx->CCR3 = ccr; break;
	    case CHANNEL_4: TIMx->CCR4 = ccr; break;
	 }
}
