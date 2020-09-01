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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bspled.h"
#include "bspkey.h"
#include "bspds18b20.h"
#include "bsptime.h"
//#include "bspusart.h"
#include "bspoled.h"
#include "codetab.h"
#include "stdio.h"
#include  "bspsr501.h"
#include "bspbeep.h"
#include "bsp_mh_z19b.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
enum STATE
{
	SAFE = 0, RISK, DANGER

};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//#define LENGTH 100	//接收缓冲区大�???
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//uint8_t RxBuffer[LENGTH];	//接收缓冲�???
//uint8_t RecCount = 0;	//接收数据个数
//uint8_t RxFlag = 0;	//接收完成标志�???0表示接收未完成，1表示接收完成
//DMA_HandleTypeDef hdma_usart1_rx;
//DMA_HandleTypeDef hdma_usart1_tx;
uint8_t isStart = 0;
float temperature = 0;
uint8_t dis_buf[1024] =
{ 0 };
uint8_t flag = 0;
uint8_t state = SAFE;
uint16_t co2 = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	BSP_SR501_EXTI_Config();

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	//清楚定时器初始化过程中的更新中断标志
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);
	//使能定时�???4更新中断并启动定时器
	HAL_TIM_Base_Start_IT(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
	    if (isStart == 0)
		{

		continue;
		}
		else if (isStart == 1)
		{
			BSP_KEY_Config();
			BSP_LED_Config();
			BSP_OLED_Config();
			BSP_DS18B20_Config();
			BSP_BEEP_Config();
			BSP_LED_Off(LED0);
			BSP_LED_Off(LED1);
			BSP_LED_Off(LED2);
			BSP_OLED_CLS();
		}
		else
		{
//			temperature = BSP_DS18B20_GetTemp();
		    //			sprintf((char*) dis_buf, "Temp:%0.3fC", temperature);
//			BSP_OLED_Big_Str(0, 0, dis_buf);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//			switch (state)
//			{
//			case SAFE:
//				BSP_LED_On(LED0);
//				BSP_LED_Off(LED1);
//				BSP_LED_Off(LED2);
//				BSP_BEEP_StopRing();
//				break;
//			case RISK:
//				BSP_LED_On(LED1);
//				BSP_LED_Off(LED0);
//				BSP_LED_Off(LED2);
//				BSP_BEEP_StopRing();
//				break;
//			case DANGER:
//				BSP_LED_On(LED2);
//				BSP_LED_Off(LED0);
//				BSP_LED_Off(LED1);
//				BSP_BEEP_StartRing();
//				break;
//			}

			BSP_CO2_Tx(&co2);
		sprintf((char*) dis_buf, "%u", co2);
		BSP_OLED_Big_Str(0, 0, dis_buf);

	}

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

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == TIM4)
{
	if (temperature < 29.0f)
	{
		state = SAFE;
	}
	else if (temperature < 32.0f)
	{
		state = RISK;
	}
	else
	{
		state = DANGER;
	}
}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
isStart++;
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (huart->Instance == huart1.Instance)
//	{
//		HAL_UART_Receive_DMA(&huart1, (uint8_t*) RxBuffer, RecCount);
//	}
//}
//
//void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart)
//{
//	RxFlag = 1;
//}
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
