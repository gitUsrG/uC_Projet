################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PWM/Src/pwm.c 

OBJS += \
./PWM/Src/pwm.o 

C_DEPS += \
./PWM/Src/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
PWM/Src/%.o PWM/Src/%.su PWM/Src/%.cyclo: ../PWM/Src/%.c PWM/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/PID/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/PWM/Inc" -I"C:/Users/gabyb/STM32CubeIDE/workspace_1.16.1/Projet/SCD30/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PWM-2f-Src

clean-PWM-2f-Src:
	-$(RM) ./PWM/Src/pwm.cyclo ./PWM/Src/pwm.d ./PWM/Src/pwm.o ./PWM/Src/pwm.su

.PHONY: clean-PWM-2f-Src

