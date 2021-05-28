################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/can.c \
../Src/canmd_controller.c \
../Src/gpio.c \
../Src/main.c \
../Src/ps3.c \
../Src/stm32_printf.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/stm32f4_easy_can.c \
../Src/syscalls.c \
../Src/system_stm32f3xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/can.o \
./Src/canmd_controller.o \
./Src/gpio.o \
./Src/main.o \
./Src/ps3.o \
./Src/stm32_printf.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/stm32f4_easy_can.o \
./Src/syscalls.o \
./Src/system_stm32f3xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/can.d \
./Src/canmd_controller.d \
./Src/gpio.d \
./Src/main.d \
./Src/ps3.d \
./Src/stm32_printf.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/stm32f4_easy_can.d \
./Src/syscalls.d \
./Src/system_stm32f3xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303x8 -I"D:/STM/practice03/Inc" -I"D:/STM/practice03/Drivers/STM32F3xx_HAL_Driver/Inc" -I"D:/STM/practice03/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"D:/STM/practice03/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"D:/STM/practice03/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


