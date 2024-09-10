/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  LL_RTC_InitTypeDef RTC_InitStruct = {0};
  LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
  LL_RTC_AlarmTypeDef RTC_AlarmStruct = {0};

    LL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_BKP);
  /* Peripheral clock enable */
  LL_RCC_EnableRTC();

  /* RTC interrupt Init */
  NVIC_SetPriority(RTC_Alarm_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(RTC_Alarm_IRQn);

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC and set the Time and Date
  */
  RTC_InitStruct.AsynchPrescaler = 0xFFFFFFFFU;
  LL_RTC_Init(RTC, &RTC_InitStruct);
  LL_RTC_SetAsynchPrescaler(RTC, 0xFFFFFFFFU);
  /** Initialize RTC and set the Time and Date
  */
  RTC_TimeStruct.Hours = 11;
  RTC_TimeStruct.Minutes = 45;
  RTC_TimeStruct.Seconds = 30;
  LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
  /** Initialize RTC and set the Time and Date
  */
  /** Enable the Alarm A
  */
  RTC_AlarmStruct.AlarmTime.Hours = 0x10;
  RTC_AlarmStruct.AlarmTime.Minutes = 0x45;
  RTC_AlarmStruct.AlarmTime.Seconds = 0x30;
  LL_RTC_ALARM_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_AlarmStruct);
  LL_RTC_EnableIT_ALR(RTC);
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
