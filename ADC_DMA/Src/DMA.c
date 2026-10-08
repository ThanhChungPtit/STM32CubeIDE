#include "DMA.h"
#include "ADC.h"

void DMA1_Ch1_ADC1_Init(uint32_t memory_addr, uint16_t size) {
    //Bật clock DMA1
    RCC_AHBENR |= (1U << 0);

    //Tắt Channel 1 trước khi cài đặt
    DMA1_CCR1 &= ~(1U << 0);

    // 3. Cài đặt địa chỉ Nguồn (ADC01_DR) và Đích (Mảng RAM)
    DMA1_CPAR1 = (uint32_t)&ADC01_DR;
    DMA1_CMAR1 = memory_addr;
    DMA1_CNDTR1 = size;

    /* Cấu hình mode:
       - CIRC (Bit 5) = 1  : Vòng lặp liên tục
       - MINC (Bit 7) = 1  : Tự tăng địa chỉ mảng RAM
       - PSIZE (Bit 8) = 1 : Dữ liệu nguồn 16-bit
       - MSIZE (Bit 10)= 1 : Dữ liệu đích 16-bit */
    DMA1_CCR1 = (1U << 5) | (1U << 7) | (1U << 8) | (1U << 10);

    //Bật DMA1 Channel 1
    DMA1_CCR1 |= (1U << 0);
}
