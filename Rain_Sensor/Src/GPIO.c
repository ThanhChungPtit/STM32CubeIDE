#include "GPIO.h"
void GPIO_Config(volatile GPIO_TypeDef * GPIOx, uint16_t Pin, uint16_t Mode) {
    uint32_t config = 0;
    uint8_t is_pullup = 0;
    uint8_t is_pulldown = 0;

    switch (Mode) {
       case GPIO_MODE_INPUT_ANALOG:
           config = (0x0 << 2) | (0x0 << 0);
           break;
       case GPIO_MODE_INPUT_FLOATING:
           config = (0x1 << 2) | (0x0 << 0);
           break;
       case GPIO_MODE_INPUT_PULLUP:
           config = (0x2 << 2) | (0x0 << 0);
           is_pullup = 1;
           break;
       case GPIO_MODE_INPUT_PULLDOWN:
           config = (0x2 << 2) | (0x0 << 0);
           is_pulldown = 1;
           break;
       case GPIO_MODE_OUTPUT_PP:
           config = (0x0 << 2) | (0x3 << 0); // Output 50MHz
           break;
       case GPIO_MODE_OUTPUT_OD:
           config = (0x1 << 2) | (0x3 << 0);
           break;
       case AF_MODE_OUTPUT_PP:
           config = (0x2 << 2) | (0x3 << 0);
           break;
       case AF_MODE_OUTPUT_OD:
           config = (0x3 << 2) | (0x3 << 0);
           break;
    }

    for (uint16_t i = 0; i < 16; i++) {
        if ((1 << i) & Pin) {
           // 1. Cấu hình các bit CNF và MODE trong CRL/CRH
           if (i < 8) {
              GPIOx->CRL &=~ (0xF << (i * 4));
              GPIOx->CRL |= (config << (i * 4));
           }
           else {
              GPIOx->CRH &=~ (0xF << ((i - 8) * 4));
              GPIOx->CRH |= (config << ((i - 8) * 4));
           }

           // 2. Xử lý thanh ghi ODR cho chế độ Input hoặc xóa trạng thái cũ
           if (is_pullup) {
               GPIOx->ODR |= (1 << i);
           }
           else {
               // Nếu không phải pull-up (bao gồm cả pull-down, floating, output...),
               // hạ bit ODR xuống 0 cho an toàn
               GPIOx->ODR &=~ (1 << i);
           }
        }
    }
}
