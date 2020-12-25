/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

#define RF24_SPI hspi2
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_FLASH_Pin GPIO_PIN_13
#define LED_FLASH_GPIO_Port GPIOC
#define NRF24_CSN_Pin GPIO_PIN_12
#define NRF24_CSN_GPIO_Port GPIOB
#define NRF24_CE_Pin GPIO_PIN_8
#define NRF24_CE_GPIO_Port GPIOA
#define ST7735_CS_Pin GPIO_PIN_7
#define ST7735_CS_GPIO_Port GPIOB
#define ST7735_DC_Pin GPIO_PIN_8
#define ST7735_DC_GPIO_Port GPIOB
#define ST7735_RES_Pin GPIO_PIN_9
#define ST7735_RES_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
/*
#define ST7735_RES_Pin GPIO_PIN_2
#define ST7735_RES_GPIO_Port GPIOA
#define ST7735_DC_Pin GPIO_PIN_3
#define ST7735_DC_GPIO_Port GPIOA
#define ST7735_CS_Pin GPIO_PIN_4
#define ST7735_CS_GPIO_Port GPIOA

#define ENC_KEY_Pin GPIO_PIN_13
#define ENC_KEY_GPIO_Port GPIOC
#define ENC_A_Pin GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOA
*/

#define fromMX(xx) xx##_GPIO_Port, xx##_Pin

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
