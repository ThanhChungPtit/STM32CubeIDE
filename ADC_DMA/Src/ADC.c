#include "ADC.h"
#include "TIM.h"

void ADC01_Init(uint16_t channel) {
	ADC01_SMPR2 &=~ (7U<<(channel*3)) ;
	ADC01_SMPR2 |= (2U<<(channel*3)) ;//13.5

	ADC01_SQR3 &=~ (0x1FU << 0);           // Xóa 5 bit đầu tiên (SQ1)
	ADC01_SQR3 |=  ((uint32_t)channel << 0); // Gán channel vào SQ1

	ADC01_CR2 |= (1U<<1) ;//Mode chuyển đổi liên tục
	ADC01_CR2 |= (1U<<0) ;
	Delay_ms(TIM2,2000) ;
	ADC01_CR2 |= (1U<<0) ;

	ADC01_CR2 |= (1U<<3) ;
	while(ADC01_CR2 & (1U << 3)){}//RSTCAL
	ADC01_CR2 |= (1U << 2);//Enable calibration
	while(ADC01_CR2 & (1U<<2)){}//CAL
	ADC01_CR2 |= (1U<<22) ;

}

uint16_t ADC01_Read(void) {
	while(!(ADC01_SR & (1<<1))){}
	return (uint16_t)(ADC01_DR & 0xFFFF) ;
}


void ADC02_Init(uint16_t channel) {
	ADC02_SMPR2 &=~ (7U<<(channel*3)) ;
	ADC02_SMPR2 |= (2U<<(channel*3)) ;//13.5

	ADC02_SQR3 &=~ (0x1FU << 0);
	ADC02_SQR3 |=  ((uint32_t)channel << 0);

	ADC02_CR2 |= (1U<<1) ;
	ADC02_CR2 |= (1U<<0) ;
	Delay_ms(TIM2,1) ;
	ADC02_CR2 |= (1U<<0) ;

	ADC02_CR2 |= (1U<<3) ;
	while(ADC02_CR2 & (1U << 3)){}//RSTCAL
	ADC02_CR2 |= (1U << 2);//Enable calibration
	while(ADC02_CR2 & (1U<<2)){}//CAL
	ADC02_CR2 |= (1U<<22) ;

}

uint16_t ADC02_Read(void) {
	while(!(ADC02_SR & (1<<1))){}
	return (uint16_t)(ADC02_DR & 0xFFFF) ;
}


void ADC01_Init_MultiChannel(uint8_t *channels, uint8_t count) {
    /* Giới hạn an toàn tối đa 6 kênh (nếu cần nhiều hơn phải dùng thêm SQR2/SQR1) */
    if (count > 6) count = 6;

    /* 1. Reset chuỗi quét cũ trong SQR1 và SQR3 */
    ADC01_SQR1 &= ~(0xFU << 20); // Xóa cấu hình độ dài chuỗi (L)
    ADC01_SQR3 = 0;              // Xóa toàn bộ thứ tự quét cũ

    /* 2. Cài đặt số lượng kênh quét: Thanh ghi L = count - 1 */
    ADC01_SQR1 |= ((uint32_t)(count - 1) << 20);

    /* 3. Vòng lặp tự động cấu hình từng kênh truyền vào */
    for (uint8_t i = 0; i < count; i++) {
        uint8_t ch = channels[i];

        /* Cấu hình Sample time 13.5 cycles cho kênh ch trong SMPR2 */
        ADC01_SMPR2 &= ~(7U << (ch * 3));
        ADC01_SMPR2 |=  (2U << (ch * 3));

        /* Gán kênh ch vào vị trí SQ(i+1) trong SQR3 */
        ADC01_SQR3 |= ((uint32_t)ch << (i * 5));
    }

    /* 4. Cấu hình Chế độ Scan, DMA và Liên tục */
    ADC01_CR1 |= (1U << 8);  // SCAN Mode (Quét chuỗi)
    ADC01_CR2 |= (1U << 8);  // Bật DMA Request
    ADC01_CR2 |= (1U << 1);  // Continuous Mode (Chạy lặp đi lặp lại)

    /* 5. Bật nguồn & Calibration */
    ADC01_CR2 |= (1U << 0);
    Delay_ms(TIM2, 2000);
    ADC01_CR2 |= (1U << 0);

    ADC01_CR2 |= (1U << 3);
    while (ADC01_CR2 & (1U << 3)) {} // RSTCAL

    ADC01_CR2 |= (1U << 2);
    while (ADC01_CR2 & (1U << 2)) {} // CAL

    /* 6. Bắt đầu kích hoạt chuyển đổi */
    ADC01_CR2 |= (1U << 22); // SWSTART
}

