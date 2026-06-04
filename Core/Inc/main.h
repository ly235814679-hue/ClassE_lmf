/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FW_VOL_ADC_Pin GPIO_PIN_0
#define FW_VOL_ADC_GPIO_Port GPIOA
#define REF_VOL_ADC_Pin GPIO_PIN_1
#define REF_VOL_ADC_GPIO_Port GPIOA
#define CURRENT_RMS1_Pin GPIO_PIN_4
#define CURRENT_RMS1_GPIO_Port GPIOA
#define CIRRENT_RMS_2_Pin GPIO_PIN_5
#define CIRRENT_RMS_2_GPIO_Port GPIOA
#define FAN_PWM_Pin GPIO_PIN_6
#define FAN_PWM_GPIO_Port GPIOA
#define CURRENT_HW_SIG_Pin GPIO_PIN_7
#define CURRENT_HW_SIG_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define USER_BTN_Pin GPIO_PIN_2
#define USER_BTN_GPIO_Port GPIOB
#define SOL_EN_Pin GPIO_PIN_10
#define SOL_EN_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define FW_HW_SIG_Pin GPIO_PIN_8
#define FW_HW_SIG_GPIO_Port GPIOA
#define RELAY_4_Pin GPIO_PIN_9
#define RELAY_4_GPIO_Port GPIOA
#define RELAY_3_Pin GPIO_PIN_10
#define RELAY_3_GPIO_Port GPIOA
#define RELAY_2_Pin GPIO_PIN_11
#define RELAY_2_GPIO_Port GPIOA
#define RELAY_1_Pin GPIO_PIN_12
#define RELAY_1_GPIO_Port GPIOA
#define USER_IO1_Pin GPIO_PIN_3
#define USER_IO1_GPIO_Port GPIOB
#define USER_IO2_Pin GPIO_PIN_4
#define USER_IO2_GPIO_Port GPIOB
#define USER_IO3_Pin GPIO_PIN_5
#define USER_IO3_GPIO_Port GPIOB
#define EXT_BTN_Pin GPIO_PIN_6
#define EXT_BTN_GPIO_Port GPIOB
#define SYS_SIG_Pin GPIO_PIN_7
#define SYS_SIG_Port GPIOB
#define SYS_PWR_Pin GPIO_PIN_8
#define SYS_PWR_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
