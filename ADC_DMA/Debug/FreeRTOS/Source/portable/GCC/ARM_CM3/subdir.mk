################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM3/%.o FreeRTOS/Source/portable/GCC/ARM_CM3/%.su FreeRTOS/Source/portable/GCC/ARM_CM3/%.cyclo: ../FreeRTOS/Source/portable/GCC/ARM_CM3/%.c FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/CubeIDE/Cambienanhsang/FreeRTOS/Source/include" -I"D:/CubeIDE/Cambienanhsang/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"D:/CubeIDE/Cambienanhsang/FreeRTOS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.cyclo ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o ./FreeRTOS/Source/portable/GCC/ARM_CM3/port.su

.PHONY: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

