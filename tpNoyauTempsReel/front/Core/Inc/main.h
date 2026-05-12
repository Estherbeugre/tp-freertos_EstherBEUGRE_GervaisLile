/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g0xx_hal.h"

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
#define ROW5_Pin GPIO_PIN_9
#define ROW5_GPIO_Port GPIOB
#define ROW4_Pin GPIO_PIN_14
#define ROW4_GPIO_Port GPIOC
#define ROW3_Pin GPIO_PIN_15
#define ROW3_GPIO_Port GPIOC
#define WA_Pin GPIO_PIN_0
#define WA_GPIO_Port GPIOA
#define WB_Pin GPIO_PIN_1
#define WB_GPIO_Port GPIOA
#define UART_RX_FROM_BACK_Pin GPIO_PIN_2
#define UART_RX_FROM_BACK_GPIO_Port GPIOA
#define UART_TX_FROM_BACK_Pin GPIO_PIN_3
#define UART_TX_FROM_BACK_GPIO_Port GPIOA
#define COL1_Pin GPIO_PIN_5
#define COL1_GPIO_Port GPIOA
#define XA_Pin GPIO_PIN_6
#define XA_GPIO_Port GPIOA
#define XB_Pin GPIO_PIN_7
#define XB_GPIO_Port GPIOA
#define ROW1_Pin GPIO_PIN_0
#define ROW1_GPIO_Port GPIOB
#define ROW2_Pin GPIO_PIN_1
#define ROW2_GPIO_Port GPIOB
#define YA_Pin GPIO_PIN_8
#define YA_GPIO_Port GPIOA
#define YB_Pin GPIO_PIN_9
#define YB_GPIO_Port GPIOA
#define ROW6_Pin GPIO_PIN_10
#define ROW6_GPIO_Port GPIOA
#define COL4_Pin GPIO_PIN_11
#define COL4_GPIO_Port GPIOA
#define COL3_Pin GPIO_PIN_12
#define COL3_GPIO_Port GPIOA
#define ZA_Pin GPIO_PIN_5
#define ZA_GPIO_Port GPIOB
#define ZB_Pin GPIO_PIN_7
#define ZB_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_8
#define COL2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define COL2_Pin GPIO_PIN_8
#define COL2_GPIO_Port GPIOB
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
