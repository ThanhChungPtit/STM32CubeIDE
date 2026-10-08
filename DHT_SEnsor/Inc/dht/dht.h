#ifndef __DHT_H
#define __DHT_H
#include <stdint.h>

uint8_t DHT11_Read_Byte(void) ;
int DHT11_Read(uint8_t *temp, uint8_t *humi) ;


#endif
