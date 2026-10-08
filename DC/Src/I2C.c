#include "I2C.h"

void I2C_Init(void) {
	I2C_BASE->CR1 &=~ (1<<0) ;
	I2C_BASE->CR2 = 32 ;
	I2C_BASE->TRISE = 33 ;
	I2C_BASE->CCR=160 ;
	I2C_BASE->CR1 |=(1<<0) ;
}
void I2C_Start(void) {
	I2C_BASE->CR1 &=~(uint32_t)(1<<9) ;
	I2C_BASE->CR1 |=(1<<8) ;
	while(!(I2C_BASE->SR1 & (1<<0))){}
}
void I2C_Stop(void) {
	I2C_BASE->CR1 |=  (1<<9) ;
	while (I2C_BASE->CR1 & (1 << 9)) {
		    }
}
void Clear_SB() {
	(void)I2C_BASE->SR1 ;
}
void Clear_ADDR() {
	(void)I2C_BASE->SR1 ;
	(void)I2C_BASE->SR2 ;
}
void I2C_SendAdd(uint8_t Add,uint8_t rw) {
	I2C_BASE->DR = (Add<<1) | (rw & 0x01) ;
	while(!(I2C_BASE->SR1 &(1<<1))) {
		if(I2C_BASE->SR1 & (1<<10)) {// Kiểm tra cờ AF (Acknowledge Failure)
			I2C_BASE->SR1 &=~(1<<10) ;//Xóa cờ AF
			I2C_Stop() ;//Phát STOP giải phóng bus
			return ;
		}
	}
	if(rw==0) {
		Clear_ADDR() ;//Thả SCL
	}
}
void I2C_WriteByte(uint8_t data) {
	while(!(I2C_BASE->SR1 & (1<<7))) {} //Data register not empty
	I2C_BASE->DR = (data) ;
	while(!(I2C_BASE->SR1 & (1<<2))) {}//: Data byte transfer not done(BTF)
}


uint8_t I2C_ReadByte() {
	// 1. Tắt ACK ngay khi ADDR = 1 (EV6_1)
	    I2C_BASE->CR1 &= ~(1 << 10); // Clear ACK (bit 10)

	    // 2. Xóa cờ ADDR bằng cách đọc SR1 và SR2
	    Clear_ADDR() ;

	    // 3. Phát tín hiệu STOP ngay lập tức
	    I2C_BASE->CR1 |= (1 << 9);   // Set STOP (bit 9)

	    // 4. Chờ cờ RxNE = 1 (Receive buffer not empty - bit 2 trong SR1)
	    while (!(I2C_BASE->SR1 & (1 << 2))) {}

	    // 5. Đọc dữ liệu ra
	    return (uint8_t)I2C_BASE->DR;

}
