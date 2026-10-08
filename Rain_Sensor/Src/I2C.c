#include "I2C.h"
#include "TIM.h"

void I2C_Init(void) {
	I2C_BASE->CR1 &=~ (1<<0) ;
	I2C_BASE->CR2 =8 ;
	I2C_BASE->TRISE=9 ;
	I2C_BASE->CCR =40 ;
	I2C_BASE->CR1 |=(1<<0) ;
}
void I2C_Start(void) {
	I2C_BASE->CR1 &=~(uint32_t)(1<<9) ;
	I2C_BASE ->CR1 |=(1<<8) ;
	while(!(I2C_BASE->SR1 & (1<<0))){}
}
void I2C_Stop(void) {
	I2C_BASE->CR1 |=  (1<<9) ;
	while (I2C_BASE->CR1 & (1 << 9)) {
		    }
}
void I2C_SendAdd(uint8_t Add,uint8_t rw) {
	(void)I2C_BASE->SR1;
	I2C_BASE->DR =(Add<<1) | (rw & 0x01) ;
	while(!(I2C_BASE->SR1 &(1<<1))) {}//No end of address transmission
	(void)I2C_BASE->SR1 ;
	(void)I2C_BASE->SR2 ;
}
void I2C_WriteByte(uint8_t data) {
	while(!(I2C_BASE->SR1 & (1<<7))) {} //Data register not empty
	I2C_BASE->DR = (data) ;
	while(!(I2C_BASE->SR1 & (1<<2))) {}//: Data byte transfer not done(BTF)
}
