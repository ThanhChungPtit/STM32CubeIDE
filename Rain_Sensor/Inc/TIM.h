#ifndef __TIM_H
#define __TIM_H
#include <stdint.h>


typedef struct{
	volatile uint32_t CR1 ;
	volatile uint32_t CR2 ;
	volatile uint32_t SMCR ;
	volatile uint32_t DIER ;
	volatile uint32_t SR ;
	volatile uint32_t EGR ;
	volatile uint32_t CCMR1 ;
	volatile uint32_t CCMR2 ;
	volatile uint32_t CCER ;
	volatile uint32_t CNT ;
	volatile uint32_t PSC ;
	volatile uint32_t ARR ;
	volatile uint32_t RESERVED1 ;
	volatile uint32_t CCR1 ;
	volatile uint32_t CCR2 ;
	volatile uint32_t CCR3 ;
	volatile uint32_t CCR4 ;
	volatile uint32_t REVERSED2 ;
	volatile uint32_t DCR ;
	volatile uint32_t DMAR ;
} Timer ;


#define TIM2 ((volatile Timer*) 0x40000000)
#define TIM3 ((volatile Timer*) 0x40000400)
#define TIM4 ((volatile Timer*) 0x40000800)
#define TIM5 ((volatile Timer*) 0x40000C00)

void TIM_Init(volatile Timer * TIMx,uint32_t psc) ;
void Delay_ms(volatile Timer* TIMx, uint32_t ms);
void Delay_us(volatile Timer* TIMx, uint32_t us) ;
void PWM_Init(volatile Timer* TIMx, uint32_t arr) ;
void Get_Duty(uint32_t ccr,volatile Timer* TIMx);


#endif
