################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/DS18B20/bspds18b20.c 

OBJS += \
./Bsp/DS18B20/bspds18b20.o 

C_DEPS += \
./Bsp/DS18B20/bspds18b20.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/DS18B20/bspds18b20.o: ../Bsp/DS18B20/bspds18b20.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32CubeIDE/workspace/HFUT/Bsp/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bsp/DS18B20/bspds18b20.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

