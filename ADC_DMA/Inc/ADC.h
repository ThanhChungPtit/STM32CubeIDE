#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

#define ADC01_BASE      0x40012400UL
#define ADC02_BASE      0x40012800UL

/* Ép kiểu con trỏ ép địa chỉ trực tiếp - Ngắn gọn, dễ hiểu */
#define ADC01_SR        *((volatile uint32_t *)(ADC01_BASE + 0x00))
#define ADC01_CR2       *((volatile uint32_t *)(ADC01_BASE + 0x08))
#define ADC01_SMPR2     *((volatile uint32_t *)(ADC01_BASE + 0x10))
#define ADC01_DR        *((volatile uint32_t *)(ADC01_BASE + 0x4C))
#define ADC01_CR1       *((volatile uint32_t*)(ADC01_BASE + 0x04))
#define ADC01_SQR1      *((volatile uint32_t*)(ADC01_BASE + 0x2C))
#define ADC01_SQR3  *((volatile uint32_t*)(ADC01_BASE + 0x34))

#define ADC02_SR        *((volatile uint32_t *)(ADC02_BASE + 0x00))
#define ADC02_CR2       *((volatile uint32_t *)(ADC02_BASE + 0x08))
#define ADC02_SMPR2     *((volatile uint32_t *)(ADC02_BASE + 0x10))
#define ADC02_DR        *((volatile uint32_t *)(ADC02_BASE + 0x4C))
#define ADC02_CR1       *((volatile uint32_t*)(ADC02_BASE + 0x04))
#define ADC02_SQR1      *((volatile uint32_t*)(ADC02_BASE + 0x2C))
#define ADC02_SQR3  *((volatile uint32_t*)(ADC02_BASE + 0x34))

#define ADC_CHANNEL_0   0U
#define ADC_CHANNEL_1   1U
#define ADC_CHANNEL_2   2U
#define ADC_CHANNEL_3   3U
#define ADC_CHANNEL_4   4U
#define ADC_CHANNEL_5   5U
#define ADC_CHANNEL_6   6U
#define ADC_CHANNEL_7   7U
#define ADC_CHANNEL_8   8U
#define ADC_CHANNEL_9   9U

void ADC01_Init(uint16_t channel) ;
void ADC02_Init(uint16_t channel) ;
void ADC01_Init_MultiChannel(uint8_t *channels, uint8_t count) ;

uint16_t ADC01_Read(void);
uint16_t ADC02_Read(void);
#endif
