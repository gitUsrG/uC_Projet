################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SCD30/Src/scd30.c \
../SCD30/Src/scd30_app.c \
../SCD30/Src/scd_git_version.c \
../SCD30/Src/sensirion_common.c \
../SCD30/Src/sensirion_hw_i2c_implementation.c 

OBJS += \
./SCD30/Src/scd30.o \
./SCD30/Src/scd30_app.o \
./SCD30/Src/scd_git_version.o \
./SCD30/Src/sensirion_common.o \
./SCD30/Src/sensirion_hw_i2c_implementation.o 

C_DEPS += \
./SCD30/Src/scd30.d \
./SCD30/Src/scd30_app.d \
./SCD30/Src/scd_git_version.d \
./SCD30/Src/sensirion_common.d \
./SCD30/Src/sensirion_hw_i2c_implementation.d 


# Each subdirectory must supply rules for building sources it contributes
SCD30/Src/%.o SCD30/Src/%.su SCD30/Src/%.cyclo: ../SCD30/Src/%.c SCD30/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/PID/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/PWM/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/SCD30/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SCD30-2f-Src

clean-SCD30-2f-Src:
	-$(RM) ./SCD30/Src/scd30.cyclo ./SCD30/Src/scd30.d ./SCD30/Src/scd30.o ./SCD30/Src/scd30.su ./SCD30/Src/scd30_app.cyclo ./SCD30/Src/scd30_app.d ./SCD30/Src/scd30_app.o ./SCD30/Src/scd30_app.su ./SCD30/Src/scd_git_version.cyclo ./SCD30/Src/scd_git_version.d ./SCD30/Src/scd_git_version.o ./SCD30/Src/scd_git_version.su ./SCD30/Src/sensirion_common.cyclo ./SCD30/Src/sensirion_common.d ./SCD30/Src/sensirion_common.o ./SCD30/Src/sensirion_common.su ./SCD30/Src/sensirion_hw_i2c_implementation.cyclo ./SCD30/Src/sensirion_hw_i2c_implementation.d ./SCD30/Src/sensirion_hw_i2c_implementation.o ./SCD30/Src/sensirion_hw_i2c_implementation.su

.PHONY: clean-SCD30-2f-Src

