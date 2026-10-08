#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>

#define DMA1_BASE       0x40020000UL

#define DMA1_CCR1       *((volatile uint32_t*)(DMA1_BASE + 0x08))
#define DMA1_CNDTR1     *((volatile uint32_t*)(DMA1_BASE + 0x0C))
#define DMA1_CPAR1      *((volatile uint32_t*)(DMA1_BASE + 0x10))
#define DMA1_CMAR1      *((volatile uint32_t*)(DMA1_BASE + 0x14))

#define RCC_AHBENR      *((volatile uint32_t*)(0x40021000UL + 0x14))

void DMA1_Ch1_ADC1_Init(uint32_t memory_addr, uint16_t size);

#endif
