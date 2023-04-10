################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/PeopleCounter.c \
../Core/Src/VL53L1X_api.c \
../Core/Src/VL53L1X_calibration.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/vl53l1_api.c \
../Core/Src/vl53l1_api_calibration.c \
../Core/Src/vl53l1_api_core.c \
../Core/Src/vl53l1_api_debug.c \
../Core/Src/vl53l1_api_preset_modes.c \
../Core/Src/vl53l1_api_strings.c \
../Core/Src/vl53l1_core.c \
../Core/Src/vl53l1_core_support.c \
../Core/Src/vl53l1_error_strings.c \
../Core/Src/vl53l1_platform.c \
../Core/Src/vl53l1_register_funcs.c \
../Core/Src/vl53l1_silicon_core.c \
../Core/Src/vl53l1_wait.c 

OBJS += \
./Core/Src/PeopleCounter.o \
./Core/Src/VL53L1X_api.o \
./Core/Src/VL53L1X_calibration.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/vl53l1_api.o \
./Core/Src/vl53l1_api_calibration.o \
./Core/Src/vl53l1_api_core.o \
./Core/Src/vl53l1_api_debug.o \
./Core/Src/vl53l1_api_preset_modes.o \
./Core/Src/vl53l1_api_strings.o \
./Core/Src/vl53l1_core.o \
./Core/Src/vl53l1_core_support.o \
./Core/Src/vl53l1_error_strings.o \
./Core/Src/vl53l1_platform.o \
./Core/Src/vl53l1_register_funcs.o \
./Core/Src/vl53l1_silicon_core.o \
./Core/Src/vl53l1_wait.o 

C_DEPS += \
./Core/Src/PeopleCounter.d \
./Core/Src/VL53L1X_api.d \
./Core/Src/VL53L1X_calibration.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/vl53l1_api.d \
./Core/Src/vl53l1_api_calibration.d \
./Core/Src/vl53l1_api_core.d \
./Core/Src/vl53l1_api_debug.d \
./Core/Src/vl53l1_api_preset_modes.d \
./Core/Src/vl53l1_api_strings.d \
./Core/Src/vl53l1_core.d \
./Core/Src/vl53l1_core_support.d \
./Core/Src/vl53l1_error_strings.d \
./Core/Src/vl53l1_platform.d \
./Core/Src/vl53l1_register_funcs.d \
./Core/Src/vl53l1_silicon_core.d \
./Core/Src/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/PeopleCounter.cyclo ./Core/Src/PeopleCounter.d ./Core/Src/PeopleCounter.o ./Core/Src/PeopleCounter.su ./Core/Src/VL53L1X_api.cyclo ./Core/Src/VL53L1X_api.d ./Core/Src/VL53L1X_api.o ./Core/Src/VL53L1X_api.su ./Core/Src/VL53L1X_calibration.cyclo ./Core/Src/VL53L1X_calibration.d ./Core/Src/VL53L1X_calibration.o ./Core/Src/VL53L1X_calibration.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/vl53l1_api.cyclo ./Core/Src/vl53l1_api.d ./Core/Src/vl53l1_api.o ./Core/Src/vl53l1_api.su ./Core/Src/vl53l1_api_calibration.cyclo ./Core/Src/vl53l1_api_calibration.d ./Core/Src/vl53l1_api_calibration.o ./Core/Src/vl53l1_api_calibration.su ./Core/Src/vl53l1_api_core.cyclo ./Core/Src/vl53l1_api_core.d ./Core/Src/vl53l1_api_core.o ./Core/Src/vl53l1_api_core.su ./Core/Src/vl53l1_api_debug.cyclo ./Core/Src/vl53l1_api_debug.d ./Core/Src/vl53l1_api_debug.o ./Core/Src/vl53l1_api_debug.su ./Core/Src/vl53l1_api_preset_modes.cyclo ./Core/Src/vl53l1_api_preset_modes.d ./Core/Src/vl53l1_api_preset_modes.o ./Core/Src/vl53l1_api_preset_modes.su ./Core/Src/vl53l1_api_strings.cyclo ./Core/Src/vl53l1_api_strings.d ./Core/Src/vl53l1_api_strings.o ./Core/Src/vl53l1_api_strings.su ./Core/Src/vl53l1_core.cyclo ./Core/Src/vl53l1_core.d ./Core/Src/vl53l1_core.o ./Core/Src/vl53l1_core.su ./Core/Src/vl53l1_core_support.cyclo ./Core/Src/vl53l1_core_support.d ./Core/Src/vl53l1_core_support.o ./Core/Src/vl53l1_core_support.su ./Core/Src/vl53l1_error_strings.cyclo ./Core/Src/vl53l1_error_strings.d ./Core/Src/vl53l1_error_strings.o ./Core/Src/vl53l1_error_strings.su ./Core/Src/vl53l1_platform.cyclo ./Core/Src/vl53l1_platform.d ./Core/Src/vl53l1_platform.o ./Core/Src/vl53l1_platform.su ./Core/Src/vl53l1_register_funcs.cyclo ./Core/Src/vl53l1_register_funcs.d ./Core/Src/vl53l1_register_funcs.o ./Core/Src/vl53l1_register_funcs.su ./Core/Src/vl53l1_silicon_core.cyclo ./Core/Src/vl53l1_silicon_core.d ./Core/Src/vl53l1_silicon_core.o ./Core/Src/vl53l1_silicon_core.su ./Core/Src/vl53l1_wait.cyclo ./Core/Src/vl53l1_wait.d ./Core/Src/vl53l1_wait.o ./Core/Src/vl53l1_wait.su

.PHONY: clean-Core-2f-Src

