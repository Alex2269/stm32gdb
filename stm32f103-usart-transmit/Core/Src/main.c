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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

void PC13_init(void) // cmsis lib, init led pin
{
    /* Enable clock to IO port C */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    /* Set pin C13 as an output */
    GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear bits
    GPIOC->CRH |= GPIO_CRH_MODE13;  // Output mode, max 50 MHz
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // GPIO output push-pull
}

void toggle_PC13(void)
{
  GPIOC->ODR ^= 1<<13;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern void initialise_monitor_handles(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void USART1_Init(uint32_t baudrate)
{
  // GPIOA Periph clock enable
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

  // USART1 GPIO Configuration
  // PA9    ---> USART1_TX
  // PA10   ---> USART1_RX

  // Set alternate
  GPIOA->CRH |= GPIO_CRH_CNF9;
  GPIOA->CRH |= GPIO_CRH_MODE9_1; // 10: Alternate function output Push-pull

  // GPIOA->CRH |= GPIO_CRH_CNF10_0;
  // GPIOA->CRH &= ~GPIO_CRH_MODE10_0;
  // GPIOA->CRH &= ~GPIO_CRH_MODE10_1;

  // USART1 clock enable
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  USART1->BRR = (uint16_t)(SystemCoreClock/baudrate);

  USART1->CR1 |= USART_CR1_TE; // transmitter enable
  USART1->CR1 |= USART_CR1_RE; // receiver enable
  USART1->CR1 |= USART_CR1_UE; // usart enable

  // Default value
  USART1->CR2 = (uint32_t)(0x00000000);
  USART1->CR3 = (uint32_t)(0x00000000);
}

uint8_t USART1_RX(void)
{
  while ((USART1->SR & USART_SR_RXNE) == 0); // wait for RX ready
  return (uint8_t)USART1->DR;
}

void USART1_TX(uint8_t* data, uint16_t lenght)
{
  uint16_t index = 0;
  while (index<lenght)
  {
    USART1->DR = data[index];
    while ((USART1->SR & USART_SR_TXE) == 0); // wait for TX ready
    index++;
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
#ifdef SEMIHOSTING_ENABLE
  initialise_monitor_handles();
#endif
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  PC13_init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  #ifdef UART_HOSTING
   USART1_Init(9600); // speed baudrate
   char str1[80];
  #endif

  while (1)
  {
    #ifdef SEMIHOSTING_ENABLE
     printf("\nhello printf\n");
     puts("hello puts");
     for(uint32_t i = 0; i < 10e5L; i++) __asm volatile ("nop"); // simple delay
     printf("hello printf\n");
     printf("hello world!\n");
     for(uint32_t i = 0; i < 10e5L; i++) __asm volatile ("nop"); // simple delay
    #endif

    toggle_PC13();
    for(uint32_t i = 0; i < 10e5L; i++) __asm volatile ("nop"); // simple delay

    #ifdef UART_HOSTING
     for(uint8_t i = 0; i<(sizeof(str1)/sizeof(str1[0]));i++) str1[i] = 0; // clear array
     sprintf(str1,"speed = %d\n",9600);
     USART1_TX((uint8_t*)str1,sizeof(str1)/sizeof(str1[0]));
     for(uint32_t i = 0; i < 10e5L; i++) __asm volatile ("nop"); // simple delay
    #endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_16);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(64000000);
  LL_SetSystemCoreClock(64000000);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
