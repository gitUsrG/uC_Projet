################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../scd30/Src/scd30.c \
../scd30/Src/scd_git_version.c \
../scd30/Src/sensirion_common.c \
../scd30/Src/sensirion_hw_i2c_implementation.c 

OBJS += \
./scd30/Src/scd30.o \
./scd30/Src/scd_git_version.o \
./scd30/Src/sensirion_common.o \
./scd30/Src/sensirion_hw_i2c_implementation.o 

C_DEPS += \
./scd30/Src/scd30.d \
./scd30/Src/scd_git_version.d \
./scd30/Src/sensirion_common.d \
./scd30/Src/sensirion_hw_i2c_implementation.d 


# Each subdirectory must supply rules for building sources it contributes
scd30/Src/%.o scd30/Src/%.su scd30/Src/%.cyclo: ../scd30/Src/%.c scd30/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/PWMTemp/scd30/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-scd30-2f-Src

clean-scd30-2f-Src:
	-$(RM) ./scd30/Src/scd30.cyclo ./scd30/Src/scd30.d ./scd30/Src/scd30.o ./scd30/Src/scd30.su ./scd30/Src/scd_git_version.cyclo ./scd30/Src/scd_git_version.d ./scd30/Src/scd_git_version.o ./scd30/Src/scd_git_version.su ./scd30/Src/sensirion_common.cyclo ./scd30/Src/sensirion_common.d ./scd30/Src/sensirion_common.o ./scd30/Src/sensirion_common.su ./scd30/Src/sensirion_hw_i2c_implementation.cyclo ./scd30/Src/sensirion_hw_i2c_implementation.d ./scd30/Src/sensirion_hw_i2c_implementation.o ./scd30/Src/sensirion_hw_i2c_implementation.su

.PHONY: clean-scd30-2f-Src

