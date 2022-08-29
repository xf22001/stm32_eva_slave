/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f2xx_hal.h"

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
#define out_5_Pin GPIO_PIN_2
#define out_5_GPIO_Port GPIOE
#define out_4_Pin GPIO_PIN_3
#define out_4_GPIO_Port GPIOE
#define out_3_Pin GPIO_PIN_4
#define out_3_GPIO_Port GPIOE
#define out_2_Pin GPIO_PIN_5
#define out_2_GPIO_Port GPIOE
#define out_1_Pin GPIO_PIN_6
#define out_1_GPIO_Port GPIOE
#define d1_Pin GPIO_PIN_13
#define d1_GPIO_Port GPIOC
#define d2_Pin GPIO_PIN_14
#define d2_GPIO_Port GPIOC
#define d3_Pin GPIO_PIN_15
#define d3_GPIO_Port GPIOC
#define in_1_Pin GPIO_PIN_0
#define in_1_GPIO_Port GPIOC
#define in_2_Pin GPIO_PIN_2
#define in_2_GPIO_Port GPIOC
#define in_3_Pin GPIO_PIN_3
#define in_3_GPIO_Port GPIOC
#define in_4_Pin GPIO_PIN_0
#define in_4_GPIO_Port GPIOA
#define in_5_Pin GPIO_PIN_3
#define in_5_GPIO_Port GPIOA
#define in_6_Pin GPIO_PIN_5
#define in_6_GPIO_Port GPIOA
#define in_7_Pin GPIO_PIN_6
#define in_7_GPIO_Port GPIOA
#define in_b_cc1_Pin GPIO_PIN_7
#define in_b_cc1_GPIO_Port GPIOE
#define in_a_cc1_Pin GPIO_PIN_8
#define in_a_cc1_GPIO_Port GPIOE
#define relay_2_Pin GPIO_PIN_9
#define relay_2_GPIO_Port GPIOE
#define relay_3_Pin GPIO_PIN_10
#define relay_3_GPIO_Port GPIOE
#define relay_4_Pin GPIO_PIN_11
#define relay_4_GPIO_Port GPIOE
#define relay_5_Pin GPIO_PIN_12
#define relay_5_GPIO_Port GPIOE
#define relay_6_Pin GPIO_PIN_13
#define relay_6_GPIO_Port GPIOE
#define led_485_1_Pin GPIO_PIN_10
#define led_485_1_GPIO_Port GPIOD
#define led_485_2_Pin GPIO_PIN_11
#define led_485_2_GPIO_Port GPIOD
#define led_bms_Pin GPIO_PIN_12
#define led_bms_GPIO_Port GPIOD
#define led_ccs_Pin GPIO_PIN_15
#define led_ccs_GPIO_Port GPIOD
#define out_8_Pin GPIO_PIN_9
#define out_8_GPIO_Port GPIOB
#define out_7_Pin GPIO_PIN_0
#define out_7_GPIO_Port GPIOE
#define out_6_Pin GPIO_PIN_1
#define out_6_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
