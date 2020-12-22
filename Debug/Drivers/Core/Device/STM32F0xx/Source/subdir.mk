################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.c 

CPP_SRCS += \
../Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.cpp \
../Drivers/Core/Device/STM32F0xx/Source/Timers.cpp 

C_DEPS += \
./Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.d 

OBJS += \
./Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.o \
./Drivers/Core/Device/STM32F0xx/Source/Timers.o \
./Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.o 

CPP_DEPS += \
./Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.d \
./Drivers/Core/Device/STM32F0xx/Source/Timers.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.o: ../Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DSTM32F030x6 -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Core/Device/STM32F0xx/Include -I../Drivers/Library/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Drivers/Core/Device/STM32F0xx/Source/RCC_HSI_48_Init.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Core/Device/STM32F0xx/Source/Timers.o: ../Drivers/Core/Device/STM32F0xx/Source/Timers.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DSTM32F030x6 -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Core/Device/STM32F0xx/Include -I../Drivers/Library/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Drivers/Core/Device/STM32F0xx/Source/Timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.o: ../Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F030x6 -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Core/Device/STM32F0xx/Include -I../Drivers/Library/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Core/Device/STM32F0xx/Source/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

