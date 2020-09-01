################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/KEY/bspkey.c 

OBJS += \
./Bsp/KEY/bspkey.o 

C_DEPS += \
./Bsp/KEY/bspkey.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/KEY/bspkey.o: ../Bsp/KEY/bspkey.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32CubeIDE/workspace/HFUT/Bsp/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bsp/KEY/bspkey.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

