/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "PeopleCounter.h"
#include "handlers.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
VL53L1_DEV dev;
uint8_t	Dev=0x52;
int status = 0;
volatile int IntCount;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define window 15
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int8_t error;
	uint8_t byteData, sensorState=0;
	uint16_t wordData;
	uint16_t Distance;
	uint16_t avg_Distance;
	uint8_t RangeStatus;
	uint8_t dataReady;
	int center[2] = {167,231}; // these are the spad center of the 2 8*16 zones
	int Zone = 0;
	int PplCounter = 0;
	int lastPplCounter = 0;
	uint16_t measurements[window] = {0};

	uint8_t buf[128];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, RE_Pin, 1);
  HAL_GPIO_WritePin(GPIOA, DE_Pin, 1);
  HAL_GPIO_WritePin(GPIOB, XSDN_Pin, 1);
  HAL_GPIO_WritePin(GPIOB, LED_1_DI_Pin, 0);
  HAL_GPIO_WritePin(GPIOB, LED_1_DO_Pin, 0);
  HAL_GPIO_WritePin(GPIOB, LED_2_DI_Pin, 0);
  HAL_GPIO_WritePin(GPIOB, LED_2_DO_Pin, 0);
  HAL_Delay(500);
  // Those basic I2C read functions can be used to check your own I2C functions
  status = VL53L1_RdByte(dev, 0x010F, &byteData);
  sprintf(buf,"VL53L1X Model_ID: %X\n", byteData);
  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
  status = VL53L1_RdByte(dev, 0x0110, &byteData);
  sprintf(buf,"VL53L1X Module_Type: %X\n", byteData);
  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
  status = VL53L1_RdWord(dev, 0x010F, &wordData);
  sprintf(buf,"VL53L1X: %X\n", wordData);
  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
  while (sensorState == 0) {
      status = VL53L1X_BootState(dev, &sensorState);
      HAL_Delay(2);
  }

  strcpy(buf,"Chip booted\n");
  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);

  // Initialize and configure the device according to people counting need
  status = VL53L1X_SensorInit(dev);
  status += VL53L1X_SetDistanceMode(dev, 1); // 1=short, 2=long - PeopleCounter Mode 2
  status += VL53L1X_SetTimingBudgetInMs(dev, 20); // in ms possible values [20, 50, 100, 200, 500]
  status += VL53L1X_SetInterMeasurementInMs(dev, 20);
  status += VL53L1X_SetROI(dev, 4, 4); // minimum ROI 4,4 - PeopleCounter ROI 8,16
  if (status != 0) {
	  strcpy(buf,"Error in Initialization or configuration of the device\n");
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
      //return (-1);
  }

  strcpy(buf,"Start measuring oil level  ...\n");
  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
  status = VL53L1X_StartRanging(dev);   // This function has to be called to enable the ranging

  HAL_Delay(500);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	    while (dataReady == 0) {
				status = VL53L1X_CheckForDataReady(dev, &dataReady);
				HAL_Delay(2);
	    }

			dataReady = 0;
			status += VL53L1X_GetRangeStatus(dev, &RangeStatus);
			status += VL53L1X_GetDistance(dev, &Distance);
			status += VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/
			if (status != 0) {
				strcpy(buf,"Error in operating the device\n");
				HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
				//return (-1);
			}

			// wait a couple of milliseconds to ensure the setting of the new ROI center for the next ranging is effective
			// otherwise there is a risk that this setting is applied to current ranging (even if timing has expired, the intermeasurement
			// may expire immediately after.
			HAL_Delay(10);
			status = VL53L1X_SetROICenter(dev, center[Zone]);
			if (status != 0) {
				strcpy(buf,"Error in chaning the center of the ROI\n");
				HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
				//return (-1);
			}

			// inject the new ranged distance in the people counting algorithm
			/*PplCounter = ProcessPeopleCountingData(Distance, Zone);
			Zone++;
			Zone = Zone%2;*/

			/*sprintf(buf,"Zone: %d, RangeStatus: %d, Distance: %d, Counter: %d\n", Zone, RangeStatus, Distance, PplCounter);
			HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);*/

			/*if(lastPplCounter != PplCounter) {
				sprintf(buf,"Zone: %d, RangeStatus: %d, Distance: %d, Counter: %d\n", Zone, RangeStatus, Distance, PplCounter);
				HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
				lastPplCounter = PplCounter;
				  HAL_GPIO_TogglePin(GPIOB, LED_1_DO_Pin);
				  HAL_GPIO_TogglePin(GPIOB, LED_2_DO_Pin);
				  HAL_Delay(5);
				  HAL_GPIO_TogglePin(GPIOB, LED_1_DO_Pin);
				  HAL_GPIO_TogglePin(GPIOB, LED_2_DO_Pin);
			}*/

			if(1) {
				for(uint8_t i = 0; i < window-1; i++) {
					measurements[i] = measurements[i+1];
				}
				measurements[window-1] = Distance;
				avg_Distance = 0;
				for(uint8_t i = 0; i < window-1; i++) {
					avg_Distance += measurements[i];
				}
				avg_Distance = avg_Distance / window;
				if(avg_Distance>120){
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
				}else{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
				}
				sprintf(buf,"%d\r\n", avg_Distance);
				HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
				HAL_GPIO_TogglePin(GPIOB, LED_1_DO_Pin);
				HAL_GPIO_TogglePin(GPIOB, LED_2_DO_Pin);
				HAL_Delay(5);
				HAL_GPIO_TogglePin(GPIOB, LED_1_DO_Pin);
				HAL_GPIO_TogglePin(GPIOB, LED_2_DO_Pin);
			}

			HAL_Delay(50);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RE_Pin|DE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_1_DI_Pin|LED_1_DO_Pin|LED_2_DI_Pin|LED_2_DO_Pin
                          |XSDN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RST_Pin|CHPD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RE_Pin DE_Pin */
  GPIO_InitStruct.Pin = RE_Pin|DE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_1_DI_Pin LED_1_DO_Pin LED_2_DI_Pin LED_2_DO_Pin
                           XSDN_Pin */
  GPIO_InitStruct.Pin = LED_1_DI_Pin|LED_1_DO_Pin|LED_2_DI_Pin|LED_2_DO_Pin
                          |XSDN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RST_Pin CHPD_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_7|RST_Pin|CHPD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : INT_Pin */
  GPIO_InitStruct.Pin = INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(INT_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
