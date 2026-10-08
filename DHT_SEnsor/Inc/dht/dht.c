#include "dht.h"
#include "gpio.h"
#include "TIM.h"

uint8_t DHT11_Read_Byte(void) {
    uint8_t data = 0; // BẮT BUỘC: Khởi tạo bằng 0
    for(int i=0 ; i<8 ; i++) {
        // Đợi chân lên cao (bắt đầu bit mới)
        while(GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0);

        Delay_us(TIM3, 40); // Đợi 40us để định dạng bit

        if(GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1) {
            data |= (1 << (7 - i));
            // Đợi cho hết xung cao của bit 1
            while (GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1);
        }
        // Nếu sau 40us mà chân đã xuống 0 thì là bit 0, không cần làm gì thêm
    }
    return data;
}

int DHT11_Read(uint8_t *temp, uint8_t *humi) {
    uint8_t buf[5] = {0, 0, 0, 0, 0};

    // 1. Tín hiệu START
    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP);
    GPIO_WritePin(GPIOA, GPIO_PIN_0, 0); // Kéo thấp
    Delay_ms(TIM2, 20);                  // Giữ 20ms

    GPIO_WritePin(GPIOA, GPIO_PIN_0, 1); // Kéo cao lại
    Delay_us(TIM3, 30);                  // Đợi 30us (Rất quan trọng)

    // 2. Kiểm tra RESPONSE
    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT_FLOATING);

    if(GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0) {
        // Đợi DHT kéo lên cao (~80us)
        while (GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0);
        // Đợi DHT kéo xuống thấp lại (~80us) để bắt đầu truyền 40 bit
        while (GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1);

        // 3. Đọc 5 bytes
        for (int i = 0; i < 5; i++) {
            buf[i] = DHT11_Read_Byte();
        }

        // 4. Kiểm tra Checksum
        if(buf[0] + buf[1] + buf[2] + buf[3] == buf[4]) {
            *humi = buf[0];
            *temp = buf[2];
            return 0; // OK
        }
    }
    return -1; // Error
}
