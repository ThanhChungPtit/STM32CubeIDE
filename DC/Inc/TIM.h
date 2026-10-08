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
} TIM_TypeDef ;


#define TIM2 ((volatile TIM_TypeDef*) 0x40000000)
#define TIM3 ((volatile TIM_TypeDef*) 0x40000400)
#define TIM4 ((volatile TIM_TypeDef*) 0x40000800)
#define TIM5 ((volatile TIM_TypeDef*) 0x40000C00)

#define CHANNEL_1 0x01
#define CHANNEL_2 0x02
#define CHANNEL_3 0x04
#define CHANNEL_4 0x08

void TIM_Init(volatile TIM_TypeDef* TIMx,uint32_t psc) ;
void Delay_ms(volatile TIM_TypeDef* TIMx, uint32_t ms);
void Delay_us(volatile TIM_TypeDef* TIMx, uint32_t us) ;
void PWM_Init(volatile TIM_TypeDef* TIMx, uint32_t arr,uint16_t channel) ;
void Set_Duty(uint32_t ccr,volatile TIM_TypeDef* TIMx, uint16_t channel) ;

#endif
