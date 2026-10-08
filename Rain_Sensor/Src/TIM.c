#include "TIM.h"



void TIM_Init(volatile Timer * TIMx,uint32_t psc) {
	TIMx->CR1 &=~(1<<0) ;//disable
	TIMx->CNT=0 ;
	TIMx->SR &=~(1<<0) ;//clear update flag
	TIMx->PSC=psc-1 ;
	TIMx->EGR |=(1<<0) ;
}
void Delay_ms(volatile Timer* TIMx, uint32_t ms) {
	if (ms==0) return ;
	TIMx->ARR=ms-1 ;
	TIMx->CNT=0 ;
	TIMx->SR &=~(1<<0) ;//clear flag update
	TIMx->CR1 |=(1<<0) ;//enable
	while(!(TIMx->SR & (1 << 0))) {}
	TIMx->CR1 &=~(1<<0) ;

}
void Delay_us(volatile Timer* TIMx, uint32_t us) {
	TIMx->ARR=us ;
	TIMx->CNT=0 ;
	TIMx->SR &=~(1<<0) ;
	TIMx->CR1 |=(1<<0) ;//enable
	while(!(TIMx->SR & (1 << 0))) {}
	TIMx->CR1 &=~(1<<0) ;
}

void PWM_Init(volatile Timer* TIMx,uint32_t arr) {
	TIMx->ARR=arr-1 ;
	TIMx->CCMR1 |=(6<<4) | (1<<3) ;//PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive
	TIMx->CCER |=(1<<0) ;// enable output
	TIMx->CR1 |= (1 << 7);     // ARPE: Auto-reload preload enable
	TIMx->EGR |=(1<<0) ;//generate update event
	TIMx->CR1 |=(1<<0) ; //enable counter
}
void Get_Duty(uint32_t ccr,volatile Timer* TIMx){
	TIMx->CCR1=ccr;
}
