################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TFT-ST7735/fonts.c \
../Drivers/TFT-ST7735/st7735.c 

C_DEPS += \
./Drivers/TFT-ST7735/fonts.d \
./Drivers/TFT-ST7735/st7735.d 

OBJS += \
./Drivers/TFT-ST7735/fonts.o \
./Drivers/TFT-ST7735/st7735.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TFT-ST7735/fonts.o: ../Drivers/TFT-ST7735/fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/RF24/utility/STM32HAL" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/TFT-ST7735" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/RF24" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -includestdint.h -include"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/hal_ardu.h" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT-ST7735/fonts.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/TFT-ST7735/st7735.o: ../Drivers/TFT-ST7735/st7735.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/RF24/utility/STM32HAL" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/TFT-ST7735" -I"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/RF24" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -includestdint.h -include"/home/me/Project-eclipse/stm32cubeIDE/IsmSannerNrf24St7735/Drivers/hal_ardu.h" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT-ST7735/st7735.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

