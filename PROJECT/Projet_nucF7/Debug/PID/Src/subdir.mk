################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PID/Src/pid_controller.c \
../PID/Src/pid_controller_config.c 

OBJS += \
./PID/Src/pid_controller.o \
./PID/Src/pid_controller_config.o 

C_DEPS += \
./PID/Src/pid_controller.d \
./PID/Src/pid_controller_config.d 


# Each subdirectory must supply rules for building sources it contributes
PID/Src/%.o PID/Src/%.su PID/Src/%.cyclo: ../PID/Src/%.c PID/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet_nucF7/PID/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet_nucF7/SCD30/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet_nucF7/PWM/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PID-2f-Src

clean-PID-2f-Src:
	-$(RM) ./PID/Src/pid_controller.cyclo ./PID/Src/pid_controller.d ./PID/Src/pid_controller.o ./PID/Src/pid_controller.su ./PID/Src/pid_controller_config.cyclo ./PID/Src/pid_controller_config.d ./PID/Src/pid_controller_config.o ./PID/Src/pid_controller_config.su

.PHONY: clean-PID-2f-Src

