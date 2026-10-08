#ifndef __GPIO_H
#define __GPIO_H
#include <stdint.h>

typedef struct {
	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR ;

} GPIO_TypeDef ;


#define GPIOA ((volatile GPIO_TypeDef*) 0x40010800)
#define GPIOB ((volatile GPIO_TypeDef*) 0x40010C00)
#define GPIOC ((volatile GPIO_TypeDef*) 0x40011000)

//GPIO PIN
#define GPIO_PIN_0   	   ((uint16_t)0x0001)
#define GPIO_PIN_1   	   ((uint16_t)0x0002)
#define GPIO_PIN_2   	   ((uint16_t)0x0004)
#define GPIO_PIN_3   	   ((uint16_t)0x0008)
#define GPIO_PIN_4   	   ((uint16_t)0x0010)
#define GPIO_PIN_5   	   ((uint16_t)0x0020)
#define GPIO_PIN_6   	   ((uint16_t)0x0040)
#define GPIO_PIN_7   	   ((uint16_t)0x0080)
#define GPIO_PIN_8   	   ((uint16_t)0x0100)
#define GPIO_PIN_9   	   ((uint16_t)0x0200)
#define GPIO_PIN_10   	   ((uint16_t)0x0400)
#define GPIO_PIN_11   	   ((uint16_t)0x0800)
#define GPIO_PIN_12   	   ((uint16_t)0x1000)
#define GPIO_PIN_13   	   ((uint16_t)0x2000)
#define GPIO_PIN_14   	   ((uint16_t)0x4000)
#define GPIO_PIN_15   	   ((uint16_t)0x8000)

#define GPIO_MODE_INPUT_FLOATING      0x00
#define GPIO_MODE_OUTPUT_PP           0x01
#define GPIO_MODE_OUTPUT_OD           0x02
#define AF_MODE_OUTPUT_PP             0x03
#define AF_MODE_OUTPUT_OD             0x04
#define GPIO_MODE_INPUT_ANALOG        0x05
#define GPIO_MODE_INPUT_PULLUP        0x06
#define GPIO_MODE_INPUT_PULLDOWN      0x07

void GPIO_Config(volatile GPIO_TypeDef * GPIOx, uint16_t Pin, uint16_t Mode) ;
void GPIO_WritePin(volatile GPIO_TypeDef * GPIOx, uint16_t Pin, uint8_t state) ;
uint8_t GPIO_ReadPin(volatile GPIO_TypeDef * GPIOx, uint16_t Pin) ;


#endif
