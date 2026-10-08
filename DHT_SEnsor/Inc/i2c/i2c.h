#ifndef __I2C_H
#define __I2C_H
#include <stdint.h>



typedef struct {
	volatile uint32_t CR1 ;
	volatile uint32_t CR2 ;
	volatile uint32_t OAR1 ;
	volatile uint32_t OAR2 ;
	volatile uint32_t DR ;
	volatile uint32_t SR1 ;
	volatile uint32_t SR2 ;
	volatile uint32_t CCR ;
	volatile uint32_t TRISE ;
} I2C_Typedef ;


#define I2C1 ((volatile I2C_Typedef *) 0x40005400)
#define I2C2 ((volatile I2C_Typedef *) 0x40005800)




void I2C_Init(void) ;
void I2C_Start(void) ;
void I2C_Stop(void) ;
void I2C_SendAdd(uint8_t Add,uint8_t rw) ;
void I2C_WriteByte(uint8_t data) ;
uint8_t I2C_ReadByte(uint8_t ack) ;


#endif
