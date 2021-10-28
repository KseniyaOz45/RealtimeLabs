/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include <inttypes.h>
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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

void Flash_Erase_One_Page(uint32_t);
void Flash_Write_uint32(uint32_t, uint32_t);
void Flash_Write_uint16(uint32_t, uint16_t);
void Flash_Write_uint64(uint32_t, uint64_t);
uint32_t Flash_Read_uint32(uint32_t);
uint16_t Flash_Read_uint16(uint32_t);
uint64_t Flash_Read_uint64(uint32_t);
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  uint32_t SIZE_ONE_PAGE = 0x400;
  uint32_t ADDR_FLASH_PAGE = 0x08000000 + 31 * SIZE_ONE_PAGE;

  uint16_t SIZE_ONE_PAGE_16 = 0x400;
  uint16_t ADDR_FLASH_PAGE_16 = 0x08000000 + 15 * SIZE_ONE_PAGE_16;

  uint64_t SIZE_ONE_PAGE_64 = 0x400;
  uint64_t ADDR_FLASH_PAGE_64 = 0x08000000 + 63 * SIZE_ONE_PAGE_64;

  size_t SIZE_uint32 = sizeof(uint32_t);
  size_t SIZE_uint16 = sizeof(uint16_t);
  size_t SIZE_uint64 = sizeof(uint64_t);

  uint32_t val_000 = 0x01234567;
  uint32_t val_004 = 0x89ABCDEF;
  uint32_t val_00C = 0x01020304;
  uint32_t val_3FC = 0x0000FFFF;

  uint16_t val_000_16 = val_000;
  uint16_t val_004_16 = val_004;
  uint16_t val_00C_16 = val_00C;
  uint16_t val_3FC_16 = val_3FC;

  uint64_t val_000_64 = val_000;
  uint64_t val_004_64 = val_004;
  uint64_t val_00C_64 = val_00C;
  uint64_t val_3FC_64 = val_3FC;

  //HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 31!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
  //Flash_Erase_One_Page(ADDR_FLASH_PAGE); // очищення 32 сторінки
  //HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 31!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
  //Flash_Erase_One_Page(ADDR_FLASH_PAGE_16); // очищення 16 сторінки
  HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 64!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
  Flash_Erase_One_Page(ADDR_FLASH_PAGE_64); // очищення 64 сторінки


  HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
  // запис значень на початку і в кінці 127 сторінки
  //Flash_Write_uint32(ADDR_FLASH_PAGE + 0 * SIZE_uint32, val_000);
  //Flash_Write_uint32(ADDR_FLASH_PAGE + 1 * SIZE_uint32, val_004);
  //Flash_Write_uint32(ADDR_FLASH_PAGE + 3 * SIZE_uint32, val_00C);
  //Flash_Write_uint32(ADDR_FLASH_PAGE + 255 * SIZE_uint32, val_3FC);

  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 + 0 * SIZE_uint16, val_000_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 + 1 * SIZE_uint16, val_004_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 + 3 * SIZE_uint16, val_00C_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 + 255 * SIZE_uint16, val_3FC_16);

  Flash_Write_uint64(ADDR_FLASH_PAGE_64 + 0 * SIZE_uint64, val_000_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 + 1 * SIZE_uint64, val_004_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 + 3 * SIZE_uint64, val_00C_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 + 255 * SIZE_uint64, val_3FC_64);

  //HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Erase page 30!!!\n\r", sizeof("\n!!!Erase page 30!!!\n\r"), 100);
  //Flash_Erase_One_Page(ADDR_FLASH_PAGE - SIZE_ONE_PAGE); // очищення 30 сторінки

  //HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Erase page 30!!!\n\r", sizeof("\n!!!Erase page 30!!!\n\r"), 100);
  //Flash_Erase_One_Page(ADDR_FLASH_PAGE_16 - SIZE_ONE_PAGE_16); // очищення 30 сторінки

  HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Erase page 63!!!\n\r", sizeof("\n!!!Erase page 63!!!\n\r"), 100);
  Flash_Erase_One_Page(ADDR_FLASH_PAGE_64 - SIZE_ONE_PAGE_64); // очищення 30 сторінки

  HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
  // запис значень на початку і в кінці 126 сторінки
  //Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x000, val_000);
  //Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x004, val_004);
  //Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x00C, val_00C);
  //Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x3FC, val_3FC);

  // запис значень на початку і в кінці 126 сторінки
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 - SIZE_ONE_PAGE_16 + 0x000, val_000_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 - SIZE_ONE_PAGE_16 + 0x004, val_004_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 - SIZE_ONE_PAGE_16 + 0x00C, val_00C_16);
  //Flash_Write_uint16(ADDR_FLASH_PAGE_16 - SIZE_ONE_PAGE_16 + 0x3FC, val_3FC_16);

  // запис значень на початку і в кінці 126 сторінки
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 - SIZE_ONE_PAGE_64 + 0x000, val_000_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 - SIZE_ONE_PAGE_64 + 0x004, val_004_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 - SIZE_ONE_PAGE_64 + 0x00C, val_00C_64);
  Flash_Write_uint64(ADDR_FLASH_PAGE_64 - SIZE_ONE_PAGE_64 + 0x3FC, val_3FC_64);

  HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Read!!!\n\r", sizeof("\n!!!Read!!!\n\r"), 100);
  // читання значень з 31 сторінки Flash-пам'яті
  //uint32_t a = Flash_Read_uint32(ADDR_FLASH_PAGE + 0 * SIZE_uint32);
  //uint32_t b = Flash_Read_uint32(ADDR_FLASH_PAGE + 1 * SIZE_uint32);
  //uint32_t c = Flash_Read_uint32(ADDR_FLASH_PAGE + 3 * SIZE_uint32);
  //uint32_t d = Flash_Read_uint32(ADDR_FLASH_PAGE + 255 * SIZE_uint32);

  // читання значень з 31 сторінки Flash-пам'яті
  //uint16_t a = Flash_Read_uint16(ADDR_FLASH_PAGE_16 + (0 * SIZE_uint16));
  //uint16_t b = Flash_Read_uint16(ADDR_FLASH_PAGE_16 + 1 * SIZE_uint16);
  //uint16_t c = Flash_Read_uint16(ADDR_FLASH_PAGE_16 + 3 * SIZE_uint16);
  //uint16_t d = Flash_Read_uint16(ADDR_FLASH_PAGE_16 + 255 * SIZE_uint16);

  // читання значень з 31 сторінки Flash-пам'яті
  uint64_t a = Flash_Read_uint64(ADDR_FLASH_PAGE_64 + (0 * SIZE_uint64));
  uint64_t b = Flash_Read_uint64(ADDR_FLASH_PAGE_64 + 1 * SIZE_uint64);
  uint64_t c = Flash_Read_uint64(ADDR_FLASH_PAGE_64 + 3 * SIZE_uint64);
  uint64_t d = Flash_Read_uint64(ADDR_FLASH_PAGE_64 + 255 * SIZE_uint64);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void Flash_Erase_One_Page(uint32_t MYADDR)
{
	FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = MYADDR;
	EraseInitStruct.NbPages = 1;

	uint32_t page_error = 0;

	char str[64] = {0, };

	HAL_FLASH_Unlock();

	if(HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK)
	{
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Erase(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		//while(1){}
	}

	snprintf(str, 64, "Erase Flash from address 0x%08lX to address 0x%08lX OK\n\r", MYADDR, MYADDR+0x400-1);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	HAL_FLASH_Lock();
}

void Flash_Write_uint32(uint32_t MYADDR, uint32_t val)
{
	char str[64] = { 0, };

	HAL_FLASH_Unlock();

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, MYADDR, val) != HAL_OK)
	{
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		//while (1){}

	}

	snprintf(str, 64, "Write 32 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	HAL_FLASH_Lock();
}

void Flash_Write_uint16(uint32_t MYADDR, uint16_t val)
{
	char str[64] = { 0, };

		HAL_FLASH_Unlock();

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, MYADDR, val) != HAL_OK)
		{
			uint32_t er = HAL_FLASH_GetError();
			snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
			HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
			//while (1){}

		}

		snprintf(str, 64, "Write 16 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		HAL_FLASH_Lock();

}

void Flash_Write_uint64(uint32_t MYADDR, uint64_t val)
{
	char str[64] = { 0, };

		HAL_FLASH_Unlock();

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, MYADDR, val) != HAL_OK)
		{
			uint32_t er = HAL_FLASH_GetError();
			snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
			HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
			//while (1){}

		}

		snprintf(str, 64, "Write 16 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		HAL_FLASH_Lock();

}

uint32_t Flash_Read_uint32(uint32_t MYADDR)
{
	char str[64] = { 0, };

	uint32_t dig32 = *(uint32_t*) MYADDR; // читання числа за його адресою
	snprintf(str, 64, "Read 32 bits (Dec: %lu \tHex: 0x%08lX)", dig32, dig32);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	return dig32;
}


uint16_t Flash_Read_uint16(uint32_t MYADDR)
{
	char str[64] = { 0, };

	uint16_t dig16 = *(uint32_t*) MYADDR;
	snprintf(str, 64, "Read 16 bits (Dec: %lu \tHex: 0x%08lX)", dig16, dig16);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	return dig16;
}

uint64_t Flash_Read_uint64(uint32_t MYADDR)
{
	char str[64] = { 0, };

	uint64_t dig64 = *(uint64_t*) MYADDR;
	snprintf(str, 64, "Read 16 bits (Dec: %lu \tHex: 0x%08lX)", dig64, dig64);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	return dig64;
}



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
