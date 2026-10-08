#include "OLED.h"
#include "TIM.h"
#include "FONT.h"
#include <math.h>
#include <stdlib.h>

static uint8_t OLED_Buffer[1024];
// 128 c?t * 8 page = 1024 bytes
void OLED_WriteCommand( uint8_t cmd) {
	I2C_Start() ;
	I2C_SendAdd(OLED_Add,0) ;//write
	I2C_WriteByte(0x00) ;//write command
	I2C_WriteByte(cmd) ;
	I2C_Stop() ;
}
void OLED_WriteData(uint8_t Data) {
	I2C_Start() ;
	I2C_SendAdd(OLED_Add,0) ;
	I2C_WriteByte(0x40) ;//write data
	I2C_WriteByte(Data) ;
	I2C_Stop() ;

}
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= 128 || y >= 64) return;

    if (color)
        OLED_Buffer[x + (y / 8) * 128] |= (1 << (y % 8)); // B?t pixel
    else
        OLED_Buffer[x + (y / 8) * 128] &= ~(1 << (y % 8)); // T?t pixel
}
void OLED_Clear() {
	for (uint8_t i = 0; i < 8; i++) {
        OLED_WriteCommand(0xB0 + i); // Chuyen sang Page i (0-7)
        OLED_WriteCommand(0x00);     // Set cot thap ve 0
        OLED_WriteCommand(0x10);     // Set cot cao ve 0

        for (uint8_t j = 0; j < 128; j++) {
            OLED_WriteData(0x00);    // Ghi du lieu trang (tat het pixel)
        }
    }
}

void OLED_SetCursor(uint8_t page, uint8_t column) {
    OLED_WriteCommand(0xB0 + page);             // Chon Page
    OLED_WriteCommand(0x00 | (column & 0x0F));  // Cot thap
    OLED_WriteCommand(0x10 | (column >> 4));    // Cot cao
}
void OLED_Init() {
	Delay_ms(TIM3,100) ; // Ð?i màn hình ?n d?nh ngu?n

    OLED_WriteCommand(0xAE); // Display OFF
    OLED_WriteCommand(0x20); // Set Memory Addressing Mode
    OLED_WriteCommand(0x10); // 00:Horizontal; 01:Vertical; 10:Page (thông d?ng nh?t)
    OLED_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode
    OLED_WriteCommand(0xC8); // Set COM Output Scan Direction
    OLED_WriteCommand(0x00); // ---set low column address
    OLED_WriteCommand(0x10); // ---set high column address
    OLED_WriteCommand(0x40); // --set start line address
    OLED_WriteCommand(0x81); // --set contrast control register
    OLED_WriteCommand(0xFF);
    OLED_WriteCommand(0xA1); // --set segment re-map 0 to 127
    OLED_WriteCommand(0xA6); // --set normal display
    OLED_WriteCommand(0xA8); // --set multiplex ratio(1 to 64)
    OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xA4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    OLED_WriteCommand(0xD3); // -set display offset
    OLED_WriteCommand(0x00); // -not offset
    OLED_WriteCommand(0xD5); // --set display clock divide ratio/oscillator frequency
    OLED_WriteCommand(0xF0); // --set divide ratio
    OLED_WriteCommand(0xD9); // --set pre-charge period
    OLED_WriteCommand(0x22);
    OLED_WriteCommand(0xDA); // --set com pins hardware configuration
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0xDB); // --set vcomh
    OLED_WriteCommand(0x20); // 0x20,0.77xVcc
    OLED_WriteCommand(0x8D); // --set DC-DC enable
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF); // --turn on oled panel

    OLED_Clear(); // Xóa màn hình lúc kh?i d?ng
}


void OLED_Update(void) {
    for (uint8_t i = 0; i < 8; i++) {
        // Thi?t l?p v? trí b?t d?u c?a Page
        OLED_WriteCommand(0xB0 + i);
        OLED_WriteCommand(0x00);
        OLED_WriteCommand(0x10);

        // B?t d?u g?i d? li?u m?ng
        I2C_Start();
        I2C_SendAdd(OLED_Add, 0);
        I2C_WriteByte(0x40); // Control byte: D? li?u liên ti?p

        for (uint16_t j = 0; j < 128; j++) {
            // G?i tr?c ti?p byte t? b? d?m
            while(!(I2C_BASE->SR1 & (1<<7))); // Ch? TXE
            I2C_BASE->DR = OLED_Buffer[j + (i * 128)];
        }

        // Ch? byte cu?i cùng g?i xong m?i Stop
        while(!(I2C_BASE->SR1 & (1<<2))); // Ch? BTF
        I2C_Stop();
    }
}
void OLED_ClearBuffer(void) {
    for (uint16_t i = 0; i < 1024; i++) {
        OLED_Buffer[i] = 0x00;
    }
}
void OLED_PutChar(char c) {
    if (c < 32 || c > 126) c = ' '; // Ch?n các ký t? ngoài t?m hi?n th?

    uint16_t font_index = (c - 32) * 5; // M?i ký t? có 5 byte

    for (uint8_t i = 0; i < 5; i++) {
        OLED_WriteData(Font5x7[font_index + i]);
    }
    OLED_WriteData(0x00); // Kho?ng cách 1 pixel gi?a các ch? cho d?p
}
void Oled_PutString(char *str) {
	while (*str) {
        OLED_PutChar(*str++);
    }
}


void OLED_DrawLine(int x0, int y0, int x1, int y1, uint8_t color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        OLED_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}


void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
    OLED_DrawLine(x, y, x + w, y, color);           // C?nh trên
    OLED_DrawLine(x, y + h, x + w, y + h, color);   // C?nh du?i
    OLED_DrawLine(x, y, x, y + h, color);           // C?nh trái
    OLED_DrawLine(x + w, y, x + w, y + h, color);   // C?nh ph?i
}

void OLED_DrawCircle(int8_t x0, int8_t y0, int8_t r, uint8_t color) {
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y) {
        OLED_DrawPixel(x0 + x, y0 + y, color);
        OLED_DrawPixel(x0 + y, y0 + x, color);
        OLED_DrawPixel(x0 - y, y0 + x, color);
        OLED_DrawPixel(x0 - x, y0 + y, color);
        OLED_DrawPixel(x0 - x, y0 - y, color);
        OLED_DrawPixel(x0 - y, y0 - x, color);
        OLED_DrawPixel(x0 + y, y0 - x, color);
        OLED_DrawPixel(x0 + x, y0 - y, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void OLED_DrawSmiley(void) {
    OLED_ClearBuffer(); // Xóa s?ch b? d?m tru?c khi v?

    // 1. V? khuôn m?t (Hình tròn l?n ? gi?a)
    // T?a d? tâm (64, 32), bán kính 30
    OLED_DrawCircle(64, 32, 30, 1);

    // 2. V? m?t trái và m?t ph?i
    OLED_DrawPixel(54, 25, 1);
    OLED_DrawPixel(55, 25, 1);
    OLED_DrawPixel(73, 25, 1);
    OLED_DrawPixel(74, 25, 1);

    // 3. V? mi?ng cu?i (Dùng các do?n th?ng nh? n?i l?i)
    OLED_DrawLine(54, 45, 60, 50, 1);
    OLED_DrawLine(60, 50, 68, 50, 1);
    OLED_DrawLine(68, 50, 74, 45, 1);

    OLED_Update(); // Ð?y d? li?u t? Buffer lên màn hình OLED
}

// 1. Hàm vẽ 1 ký tự vào bộ đệm OLED_Buffer
void OLED_PutChar_Buffer(uint8_t x, uint8_t page, char c) {
    if (x > 122 || page > 7) return;
    if (c < 32 || c > 126) c = ' ';

    uint16_t font_index = (c - 32) * 5;

    for (uint8_t i = 0; i < 5; i++) {
        OLED_Buffer[x + i + (page * 128)] = Font5x7[font_index + i];
    }
    OLED_Buffer[x + 5 + (page * 128)] = 0x00; // Pixel khoảng cách giữa các chữ
}

// 2. Hàm vẽ 1 chuỗi vào bộ đệm OLED_Buffer
void OLED_PutStr_Buffer(uint8_t x, uint8_t page, char *str) {
    while (*str) {
        if (x > 122) break;
        OLED_PutChar_Buffer(x, page, *str++);
        x += 6; // Move sang vị trí ký tự tiếp theo
    }
}

void OLED_Display_MotorInfo(uint32_t ccr_input, uint32_t current_ccr, uint8_t dir) {
    char buf[20];

    // Xóa sạch bộ đệm trước khi vẽ khung mới
    OLED_ClearBuffer();

    // Line 0 (Page 0): Tiêu đề
    OLED_PutStr_Buffer(8, 0, "=== MOTOR CONTROL ===");
    OLED_DrawLine(0, 9, 127, 9, 1); // Đường gạch kẻ ngang phân cách

    // Line 1 (Page 2): CCR đang nhập từ bàn phím
    sprintf(buf, "INPUT CCR : %lu", ccr_input);
    OLED_PutStr_Buffer(0, 2, buf);

    // Line 2 (Page 4): CCR thực tế đang phát PWM
    sprintf(buf, "RUNNING   : %lu", current_ccr);
    OLED_PutStr_Buffer(0, 4, buf);

    // Line 3 (Page 6): Duty Cycle % và Chiều quay
    sprintf(buf, "DUTY:%lu%%  DIR:%s",
            (current_ccr * 100) / 1000,
            dir ? "FWD" : "REV");
    OLED_PutStr_Buffer(0, 6, buf);

    // Đẩy toàn bộ RAM Buffer lên màn hình OLED qua I2C
    OLED_Update();
}
