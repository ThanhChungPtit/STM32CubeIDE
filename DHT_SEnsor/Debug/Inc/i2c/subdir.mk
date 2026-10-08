################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/i2c/i2c.c 

OBJS += \
./Inc/i2c/i2c.o 

C_DEPS += \
./Inc/i2c/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/i2c/%.o Inc/i2c/%.su Inc/i2c/%.cyclo: ../Inc/i2c/%.c Inc/i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/CubeIDE/DHT11/Inc/Timer" -I"D:/CubeIDE/DHT11/Inc/clock" -I"D:/CubeIDE/DHT11/Inc/dht" -I"D:/CubeIDE/DHT11/Inc/gpio" -I"D:/CubeIDE/DHT11/Inc/i2c" -I"D:/CubeIDE/DHT11/Inc/oled" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-i2c

clean-Inc-2f-i2c:
	-$(RM) ./Inc/i2c/i2c.cyclo ./Inc/i2c/i2c.d ./Inc/i2c/i2c.o ./Inc/i2c/i2c.su

.PHONY: clean-Inc-2f-i2c

