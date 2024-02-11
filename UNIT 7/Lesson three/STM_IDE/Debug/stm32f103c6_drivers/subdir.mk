################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f103c6_drivers/gpio.c 

OBJS += \
./stm32f103c6_drivers/gpio.o 

C_DEPS += \
./stm32f103c6_drivers/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f103c6_drivers/gpio.o: ../stm32f103c6_drivers/gpio.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Somia/STM32CubeIDE/workspace_1.4.0/stm32drivers/Inc" -I"C:/Users/Somia/STM32CubeIDE/workspace_1.4.0/stm32drivers/stm32f103c6_drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32f103c6_drivers/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

