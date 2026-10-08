#include <stdio.h>
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "ADC.h"
#include "I2C.h"
#include "OLED.h"

uint16_t val=0  ;

int main(void)
{
	RCC_Config();

	    // 2. BẬT TOÀN BỘ CLOCK CHO CÁC NGOẠI VI TRƯỚC (Bắt buộc)
	    RCC_Enable_PortA();
	    RCC_Enable_PortB();
	    RCC_Enable_TIM2();
	    RCC_Enable_TIM3();
	    RCC_Enable_ADC01();
	    RCC_Enable_I2C01();

	    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT_ANALOG); // Chân ADC Cảm biến
	    GPIO_Config(GPIOB, GPIO_PIN_6, AF_MODE_OUTPUT_OD); // SCL OLED
	    GPIO_Config(GPIOB, GPIO_PIN_7, AF_MODE_OUTPUT_OD); // SDA OLED

	    TIM_Init(TIM2, 64000);
	    TIM_Init(TIM3, 64);
	    ADC01_CH0_Init();
	    I2C_Init() ;

	    OLED_Init();
	    OLED_Clear();              // Xóa bộ đệm
	    OLED_SetCursor(0, 10);
	    Oled_PutString("OLED 0.96 READY");
	    Delay_ms(TIM2, 2000) ;
	    OLED_Update() ;

	    while(1) {
	    	val = ADC01_CH0_Read() ;
	    	OLED_Clear() ;
	    	OLED_SetCursor(3, 20);
	    	if(val < 1500) {
	    	    Oled_PutString("CO MUA   ");
	    	                }
	    	else {

	    	    Oled_PutString("KO MUA   ");
	    	     }
	    	Delay_ms(TIM2, 2000) ;
	    }

}
