################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/clock/clock.c 

OBJS += \
./Inc/clock/clock.o 

C_DEPS += \
./Inc/clock/clock.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/clock/%.o Inc/clock/%.su Inc/clock/%.cyclo: ../Inc/clock/%.c Inc/clock/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/CubeIDE/DHT11/Inc/Timer" -I"D:/CubeIDE/DHT11/Inc/clock" -I"D:/CubeIDE/DHT11/Inc/dht" -I"D:/CubeIDE/DHT11/Inc/gpio" -I"D:/CubeIDE/DHT11/Inc/i2c" -I"D:/CubeIDE/DHT11/Inc/oled" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-clock

clean-Inc-2f-clock:
	-$(RM) ./Inc/clock/clock.cyclo ./Inc/clock/clock.d ./Inc/clock/clock.o ./Inc/clock/clock.su

.PHONY: clean-Inc-2f-clock

