################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Library/Src/SButton.cpp 

OBJS += \
./Drivers/Library/Src/SButton.o 

CPP_DEPS += \
./Drivers/Library/Src/SButton.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Library/Src/SButton.o: ../Drivers/Library/Src/SButton.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DSTM32F030x6 -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Core/Device/STM32F0xx/Include -I../Drivers/Library/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Drivers/Library/Src/SButton.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

