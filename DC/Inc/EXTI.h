#ifndef __EXTI_H
#define __EXTI_H

#include <stdint.h>
#include <GPIO.h>
typedef struct {
	uint32_t IMR ;
	uint32_t EMR ;
	uint32_t RTSR ;
	uint32_t FTSR ;
	uint32_t SWIER ;
	uint32_t PR ;
} EXTI_TypeDef ;

#define EXTI ((volatile EXTI_TypeDef *) 0x40010400UL)

#define   NVIC_ISER0   *((uint32_t *)(0xE000E100UL)) //Base address of NVIC(Nested vectored interupt controller)+0x00
#define   NVIC_ISER1   *((uint32_t *)(0xE000E104UL))

#define EXTI_RISING_MODE 0x00
#define EXTI_FALLING_MODE 0x01
#define EXTI_BOTH_MODE 0x02

uint16_t Get_pin(uint16_t pin) ;
void EXTI_Init(volatile GPIO_TypeDef *GPIOx, uint16_t pin,uint8_t type) ;
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);


#endif
