################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Bsp/SYSTICK/subdir.mk
-include Bsp/SR501/subdir.mk
-include Bsp/OLED/subdir.mk
-include Bsp/MH-Z19B/subdir.mk
-include Bsp/LED/subdir.mk
-include Bsp/KEY/subdir.mk
-include Bsp/GSM/subdir.mk
-include Bsp/EXTI/subdir.mk
-include Bsp/DWTDELAY/subdir.mk
-include Bsp/DS18B20/subdir.mk
-include Bsp/BEEP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
HFUT.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
HFUT.list \

OBJCOPY_BIN += \
HFUT.bin \


# All Target
all: HFUT.elf secondary-outputs

# Tool invocations
HFUT.elf: $(OBJS) $(USER_OBJS) E:\STM32CubeIDE\workspace\HFUT\STM32F103ZETX_FLASH.ld
	arm-none-eabi-gcc -o "HFUT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\STM32CubeIDE\workspace\HFUT\STM32F103ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="HFUT.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

HFUT.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "HFUT.list"
	@echo 'Finished building: $@'
	@echo ' '

HFUT.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "HFUT.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
