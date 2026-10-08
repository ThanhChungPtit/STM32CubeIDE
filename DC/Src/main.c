#include <stdint.h>
#include <stdio.h>
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "I2C.h"
#include "OLED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

uint32_t SystemCoreClock = 64000000;

TaskHandle_t Task_Keypad_Handle=NULL ;
TaskHandle_t Task_Motor_Handle=NULL ;
TaskHandle_t Task_OLED_Handle=NULL ;

QueueHandle_t Input_Data=NULL ;
QueueHandle_t OLED_Info=NULL ;

typedef struct {
	uint32_t ccr_input ;
	uint32_t current_ccr ;
	uint8_t dir ;
} MotorState_t ;

void Keypad_Init(void);
char Keypad_GetKey(void);

void Task_Keypad(void *pvParameters);
void Task_Motor(void *pvParameters);
void Task_OLED(void *pvParameters) ;

int main () {
	RCC_Config();
	RCC_Enable_PortA();
	RCC_Enable_PortB();
	RCC_Enable_TIM2();
	RCC_Enable_TIM3();
	RCC_Enable_I2C01();

	GPIO_Config(GPIOA, GPIO_PIN_0, AF_MODE_OUTPUT_PP);
	GPIO_Config(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP);
	GPIO_Config(GPIOA, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP);
	GPIO_Config(GPIOB, GPIO_PIN_6, AF_MODE_OUTPUT_OD);
	GPIO_Config(GPIOB, GPIO_PIN_7, AF_MODE_OUTPUT_OD);

	TIM_Init(TIM3, 64000);
	I2C_Init();
	Keypad_Init();
	OLED_Init();
	TIM_Init(TIM2, 64);
	PWM_Init(TIM2, 1000, CHANNEL_1);

	GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);

	Input_Data = xQueueCreate(10,sizeof(char)) ;
	OLED_Info = xQueueCreate(1,sizeof(MotorState_t)) ;

	xTaskCreate(Task_Keypad, "KeypadTask", 128, NULL, 3, &Task_Keypad_Handle);
	xTaskCreate(Task_Motor,  "MotorTask",  128, NULL, 2, &Task_Motor_Handle);
	xTaskCreate(Task_OLED,   "OLEDTask",   256, NULL, 1, &Task_OLED_Handle);

	vTaskStartScheduler();
    while (1) {

    }
}

void Task_Keypad(void *pvParameters) {
	char key=0 ;
	while(1) {
		key = Keypad_GetKey() ;
		if(key != 0) {
			xQueueSend(Input_Data, &key, portMAX_DELAY) ;//Chờ tới khi q còn chỗ trống
		}
		vTaskDelay(pdMS_TO_TICKS(20)) ;
	}
}
void Task_Motor(void *pvParameters) {
	char key=0 ;
	uint32_t ccr_input = 0 ;
	uint32_t current_ccr = 0 ;
	uint8_t dir = 1 ;

	MotorState_t state ;
	state.ccr_input = ccr_input ;
	state.current_ccr = current_ccr ;
	state.dir = dir ;
	xQueueOverwrite(OLED_Info, &state) ;

	while(1) {
		if (xQueueReceive(Input_Data, &key, portMAX_DELAY) == pdTRUE) {//Chờ nếu queue đang trống(cho tới khi có dữ liệu truyền vào)
		   if (key >= '0' && key <= '9') {//input
		         ccr_input = ccr_input * 10 + (key - '0');
		         if (ccr_input > 1000) ccr_input = 1000;
		    }
		    else if (key == '#') { //Run
		         current_ccr = ccr_input;
		         Set_Duty(current_ccr, TIM2, CHANNEL_1);
		         ccr_input = 0;
		    }
		    else if (key == '*') { //delete
		         ccr_input = 0;
		    }
		    else if (key == 'A') { // THUẬN
		         dir = 1;
		         GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		         GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
		    }
		    else if (key == 'B') { // NGƯỢC
		         dir = 0;
		         GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
		         GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		    }
		    else if (key == 'C') { // DỪNG
		         current_ccr = 0;
		         ccr_input = 0;
		         Set_Duty(0, TIM2, CHANNEL_1);
		    }

		    state.ccr_input = ccr_input;
		    state.current_ccr = current_ccr;
		    state.dir = dir;
		    xQueueOverwrite(OLED_Info, &state);
		}
	}
}
void Task_OLED(void *pvParameters) {
	MotorState_t display_data;

	while(1) {
	   // Chờ dữ liệu mới từ Task_Motor (nằm chờ không tốn % CPU nào)
	   if (xQueueReceive(OLED_Info, &display_data, portMAX_DELAY) == pdTRUE) {
	      OLED_Display_MotorInfo(display_data.ccr_input, display_data.current_ccr, display_data.dir);
	   }
	}
}


