#ifndef __OLED_H
#define __OLED_H
#include "I2C.h"
#include "stdint.h"


#define OLED_Add 0x3C


void OLED_WriteCommand( uint8_t cmd);
void OLED_WriteData(uint8_t Data) ;
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color) ;
void OLED_Clear() ;
void OLED_SetCursor(uint8_t page, uint8_t column) ;
void OLED_Init() ;
void OLED_Update(void) ;
void OLED_ClearBuffer(void) ;
void OLED_PutChar(char c) ;
void Oled_PutString(char *str) ;
void OLED_DrawLine(int x0, int y0, int x1, int y1, uint8_t color) ;
void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void OLED_DrawCircle(int8_t x0, int8_t y0, int8_t r, uint8_t color) ;
void OLED_DrawSmiley(void) ;
void OLED_PutChar_Buffer(uint8_t x, uint8_t page, char c) ;
void OLED_PutStr_Buffer(uint8_t x, uint8_t page, char *str) ;
void OLED_Display_MotorInfo(uint32_t ccr_input, uint32_t current_ccr, uint8_t dir) ;

#endif
