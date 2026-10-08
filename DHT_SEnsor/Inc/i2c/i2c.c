#include "I2C.h"
#include "TIM.h"


void I2C_Init(void) {
	I2C1->CR1 &=~(1<<0) ;//disable
	I2C1->CR2=8;//INFORM
	I2C1->CCR=40 ;//100Khz , Freq SCL
	I2C1->TRISE=9 ;
	I2C1->CR1=(1<<0) ;//enable I2C
}
void I2C_Start(void) {
	I2C1->CR1 &=~(uint32_t)(1<<9) ;
	I2C1 ->CR1 |=(1<<8) ;
	while(!(I2C1->SR1 & (1<<0))){}
}
void I2C_Stop(void) {
	I2C1->CR1 |=(1<<9) ;
	while (I2C1->CR1 & (1 << 9)) {
	    }
}
void I2C_SendAdd(uint8_t Add,uint8_t rw) {
	(void)I2C1->SR1;
	I2C1->DR =(Add<<1) | (rw & 0x01) ;
	while(!(I2C1->SR1 &(1<<1))) {}//No end of address transmission
	(void)I2C1->SR1 ;
	(void)I2C1->SR2 ;
}
void I2C_WriteByte(uint8_t data) {
	while(!(I2C1->SR1 & (1<<7))) {} //Data register not empty
	I2C1->DR = (data) ;
	while(!(I2C1->SR1 & (1<<2))) {}//: Data byte transfer not done(BTF)



}


uint8_t I2C_ReadByte(uint8_t ack) {
    if (ack) {
        I2C1->CR1 |= (1 << 10); // Set bit ACK
    } else {
        I2C1->CR1 &= ~(1 << 10); // Clear bit ACK (g?i NACK)
        I2C1->CR1 |= (1 << 9);
    }

    while (!(I2C1->SR1 & (1 << 6))) {} // Ch? RXNE (D? li?u dã vào DR)
    return (uint8_t)I2C1->DR;
}



