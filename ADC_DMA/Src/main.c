#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "ADC.h"
#include "DMA.h"
#include "I2C.h"


TaskHandle_t xSensorTaskHandle = NULL;
TaskHandle_t xDisplayTaskHandle = NULL;
QueueHandle_t xSensorsQueue = NULL;

void vTaskReadSensor(void *pvParameters);
void vTaskDisplay(void *pvParameters);

uint32_t SystemCoreClock = 64000000;

typedef struct {
    uint8_t light_percent;
    uint8_t rain_percent;
} SensorData_t;
volatile uint16_t adc_buffer[2];
uint8_t adc_channels[2] = {ADC_CHANNEL_0, ADC_CHANNEL_1};
int main(void)
{
	RCC_Config() ;
	RCC_Enable_PortA() ;
	RCC_Enable_PortB() ;
	RCC_Enable_TIM2() ;
	RCC_Enable_TIM3() ;
	RCC_Enable_ADC01() ;
	RCC_Enable_I2C01() ;

	GPIO_Config(GPIOA,GPIO_PIN_0,GPIO_MODE_INPUT_ANALOG) ;
	GPIO_Config(GPIOA,GPIO_PIN_1,GPIO_MODE_INPUT_ANALOG) ;
	GPIO_Config(GPIOB,GPIO_PIN_6,AF_MODE_OUTPUT_OD) ;
	GPIO_Config(GPIOB,GPIO_PIN_7,AF_MODE_OUTPUT_OD) ;
	TIM_Init(TIM2, 64000) ;
	TIM_Init(TIM3,64) ;
	DMA1_Ch1_ADC1_Init((uint32_t)adc_buffer, 2);
	ADC01_Init_MultiChannel(adc_channels, 2);
	I2C_Init() ;
	OLED_Init() ;
	OLED_Clear() ;

	xSensorsQueue = xQueueCreate(5, sizeof(SensorData_t));
	if (xSensorsQueue != NULL) {
	        xTaskCreate(vTaskReadSensor, "Read_Sensor", 256, NULL, 1, &xSensorTaskHandle);
	        xTaskCreate(vTaskDisplay, "Display", 712, NULL, 1, &xDisplayTaskHandle);

	        vTaskStartScheduler();
	    }
    while(1) {

    }

}



void vTaskReadSensor(void *pvParameters) {
	SensorData_t data ;
    while(1) {
    	uint16_t raw_light = adc_buffer[0];
    	uint16_t raw_rain  = adc_buffer[1];
        data.light_percent = 100 - ((raw_light * 100) / 4095);
        data.rain_percent  = 100 - ((raw_rain  * 100) / 4095);
        xQueueSend(xSensorsQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000)) ;
    }
}

void vTaskDisplay(void *pvParameters) {
	SensorData_t rx_data;
	char str_display[20] ;

	OLED_SetCursor(0, 0);
	Oled_PutString("--- HE THONG CAM BIEN ---");
    while(1) {
    	if(xQueueReceive(xSensorsQueue,&rx_data, portMAX_DELAY)==pdPASS) {
    		sprintf(str_display, "ANH SANG: %3d%%  ", rx_data.light_percent);
    		OLED_SetCursor(2, 0);
    		Oled_PutString(str_display);

    		sprintf(str_display, "MUC MUA : %3d%%  ", rx_data.rain_percent);
    		OLED_SetCursor(4, 0);
    		Oled_PutString(str_display);

    		OLED_SetCursor(6, 0);
    		if (rx_data.rain_percent > 50) {
    		    Oled_PutString("TRANG THAI: CO MUA!   ");
    		}
    		else {
    		    Oled_PutString("TRANG THAI: TANH RAO  ");
    		}
    	}

    }
}
