#include "GPIO.h"
#include "TIM.h"

const char KEYPAD_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Hàng: PB0, PB1, PB10, PB11 (Đã đổi PB3 -> PB11 để né hoàn toàn JTAG)
const uint16_t ROW_PINS[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_10, GPIO_PIN_11};

// Cột: PB12, PB13, PB14, PB15
const uint16_t COL_PINS[4] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

void Keypad_Init(void) {
    // 1. Cấu hình 4 chân Hàng làm Output Push-Pull
    for (int i = 0; i < 4; i++) {
        GPIO_Config(GPIOB, ROW_PINS[i], GPIO_MODE_OUTPUT_PP);
        GPIO_WritePin(GPIOB, ROW_PINS[i], 1); // Đặt mặc định mức HIGH
    }

    // 2. Cấu hình 4 chân Cột làm Input Pull-Up
    for (int i = 0; i < 4; i++) {
        GPIO_Config(GPIOB, COL_PINS[i], GPIO_MODE_INPUT_PULLUP);
    }
}

char Keypad_GetKey(void) {
    for (int r = 0; r < 4; r++) {
        // Đặt tất cả các hàng lên HIGH
        for (int i = 0; i < 4; i++) {
            GPIO_WritePin(GPIOB, ROW_PINS[i], 1);
        }
        // Kéo riêng hàng r xuống LOW để quét
        GPIO_WritePin(GPIOB, ROW_PINS[r], 0);

        // Đọc 4 cột
        for (int c = 0; c < 4; c++) {
            if (GPIO_ReadPin(GPIOB, COL_PINS[c]) == 0) { // Nếu cột c bị kéo xuống LOW
                Delay_ms(TIM3, 50); // Debounce chống rung phím

                if (GPIO_ReadPin(GPIOB, COL_PINS[c]) == 0) {
                    // Timeout chờ nhả phím (tránh treo vô tận)
                    uint32_t timeout = 50000;
                    while ((GPIO_ReadPin(GPIOB, COL_PINS[c]) == 0) && timeout--);

                    return KEYPAD_MAP[r][c];
                }
            }
        }
    }
    return 0; // Không phím nào được bấm
}
