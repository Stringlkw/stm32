################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/EXTI/bspexti.c 

OBJS += \
./Bsp/EXTI/bspexti.o 

C_DEPS += \
./Bsp/EXTI/bspexti.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/EXTI/bspexti.o: ../Bsp/EXTI/bspexti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32CubeIDE/workspace/HFUT/Bsp/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bsp/EXTI/bspexti.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

