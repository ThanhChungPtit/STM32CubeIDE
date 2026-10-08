################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/oled/oled.c 

OBJS += \
./Inc/oled/oled.o 

C_DEPS += \
./Inc/oled/oled.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/oled/%.o Inc/oled/%.su Inc/oled/%.cyclo: ../Inc/oled/%.c Inc/oled/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/CubeIDE/DHT11/Inc/Timer" -I"D:/CubeIDE/DHT11/Inc/clock" -I"D:/CubeIDE/DHT11/Inc/dht" -I"D:/CubeIDE/DHT11/Inc/gpio" -I"D:/CubeIDE/DHT11/Inc/i2c" -I"D:/CubeIDE/DHT11/Inc/oled" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-oled

clean-Inc-2f-oled:
	-$(RM) ./Inc/oled/oled.cyclo ./Inc/oled/oled.d ./Inc/oled/oled.o ./Inc/oled/oled.su

.PHONY: clean-Inc-2f-oled

