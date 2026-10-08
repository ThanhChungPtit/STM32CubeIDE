################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/EXTI.c \
../Src/GPIO.c \
../Src/I2C.c \
../Src/Key_pad.c \
../Src/OLED.c \
../Src/RCC.c \
../Src/TIM.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/EXTI.o \
./Src/GPIO.o \
./Src/I2C.o \
./Src/Key_pad.o \
./Src/OLED.o \
./Src/RCC.o \
./Src/TIM.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/EXTI.d \
./Src/GPIO.d \
./Src/I2C.d \
./Src/Key_pad.d \
./Src/OLED.d \
./Src/RCC.d \
./Src/TIM.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/CubeIDE/DC/FreeRTOS/Source/include" -I"D:/CubeIDE/DC/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/EXTI.cyclo ./Src/EXTI.d ./Src/EXTI.o ./Src/EXTI.su ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/Key_pad.cyclo ./Src/Key_pad.d ./Src/Key_pad.o ./Src/Key_pad.su ./Src/OLED.cyclo ./Src/OLED.d ./Src/OLED.o ./Src/OLED.su ./Src/RCC.cyclo ./Src/RCC.d ./Src/RCC.o ./Src/RCC.su ./Src/TIM.cyclo ./Src/TIM.d ./Src/TIM.o ./Src/TIM.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

