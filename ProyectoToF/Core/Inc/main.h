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
#include "stm32f4xx_hal.h"

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

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RE_Pin GPIO_PIN_6
#define RE_GPIO_Port GPIOA
#define DE_Pin GPIO_PIN_7
#define DE_GPIO_Port GPIOA
#define LED_1_DI_Pin GPIO_PIN_12
#define LED_1_DI_GPIO_Port GPIOB
#define LED_1_DO_Pin GPIO_PIN_13
#define LED_1_DO_GPIO_Port GPIOB
#define LED_2_DI_Pin GPIO_PIN_14
#define LED_2_DI_GPIO_Port GPIOB
#define LED_2_DO_Pin GPIO_PIN_15
#define LED_2_DO_GPIO_Port GPIOB
#define SDIO_Pin GPIO_PIN_13
#define SDIO_GPIO_Port GPIOA
#define SCLK_Pin GPIO_PIN_14
#define SCLK_GPIO_Port GPIOA
#define RST_Pin GPIO_PIN_11
#define RST_GPIO_Port GPIOC
#define CHPD_Pin GPIO_PIN_12
#define CHPD_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define XSDN_Pin GPIO_PIN_8
#define XSDN_GPIO_Port GPIOB
#define INT_Pin GPIO_PIN_9
#define INT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
