/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include "scd30.h"
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

uint16_t dutyCycle = 500;



float co2_ppm, temperature, relative_humidity;
int16_t err;
uint16_t interval_in_seconds = 2;
char txbuff[200];

uint8_t rxBuffer[4] = {0};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void UART2_SendString(char* str) {
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void SetDutyCycle(uint8_t dutyCycle) {
    uint32_t compareValue = (dutyCycle * 10);
    if(compareValue > 1000) compareValue = 1000;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compareValue);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {

 //   		  if(HAL_UART_Receive(&huart2, rxBuffer, sizeof(rxBuffer)-1, HAL_MAX_DELAY) == HAL_OK){
    	rxBuffer[sizeof(rxBuffer) - 1] = '\0';
    	char* endPtr;
    	long dutyCycle = strtol((char*)rxBuffer, &endPtr, 10);

    	if (*endPtr == '\0' && dutyCycle >= 0 && dutyCycle <= 100)
    	{
    		SetDutyCycle((uint8_t)dutyCycle);
    	}
    }
    HAL_UART_Receive_IT(&huart2, rxBuffer, sizeof(rxBuffer)-1);
}


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
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */


  HAL_UART_Receive_IT(&huart2, rxBuffer, sizeof(rxBuffer)-1);


  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutyCycle);



  /* Initialize I2C */
  sensirion_i2c_init();
  /* Busy loop for initialization, because the main loop does not work without
   * a sensor.
   */

    while (scd30_probe() != NO_ERROR) {
  	  UART2_SendString("SCD30 sensor probing failed\n");
        sensirion_sleep_usec(1000000u);
    }
    UART2_SendString("SCD30 sensor probing successful\n");

    scd30_set_measurement_interval(interval_in_seconds);
    sensirion_sleep_usec(20000u);
    scd30_start_periodic_measurement(0);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  uint16_t data_ready = 0;
	        uint16_t timeout = 0;

	        /* Poll data_ready flag until data is available. Allow 20% more than
	         * the measurement interval to account for clock imprecision of the
	         * sensor.
	         */
	        for (timeout = 0; (100000 * timeout) < (interval_in_seconds * 1500000); ++timeout) {  // Augmenter le délai d'attente
	            err = scd30_get_data_ready(&data_ready);
	            if (err != NO_ERROR) {
	                sprintf(txbuff, "Error reading data_ready flag: %i\n", err);
	                UART2_SendString(txbuff);
	                break;  // Sortir de la boucle en cas d'erreur
	            }
	            if (data_ready) {
	                break;
	            }
	            sensirion_sleep_usec(100000);  // Attente de 100ms avant de re-vérifier
	        }


	        if (!data_ready) {
	            UART2_SendString("Timeout waiting for data_ready flag\n");
	            continue;
	        }

	        /* Measure co2, temperature and relative humidity and store into
	         * variables.
	         */
	        err = scd30_read_measurement(&co2_ppm, &temperature, &relative_humidity);
	        if (err != NO_ERROR) {
	            UART2_SendString("Error reading measurement\n");

	        } else {
	            sprintf(txbuff, "Measured CO2 concentration: %.2f ppm, "
	                   "Measured temperature: %.2f degC, "
	                   "Measured humidity: %.2f %%RH\r\n",
	                   co2_ppm, temperature,relative_humidity);
	            UART2_SendString(txbuff);
	        }

	        HAL_Delay(2000);  // Attente de 2 secondes avant la prochaine lecture






    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  scd30_stop_periodic_measurement();

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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
