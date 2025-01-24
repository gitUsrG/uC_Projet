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
#include "pwm.h"

#include "pid_controller_config.h"

#include "scd30.h"
#include "scd30_app.h"

#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


typedef struct {
  float measurement;
  float reference;
  float control;
} SWV_TypeDef;





/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

float setpoint = 35.0f;
float duty = 50.0f;

uint16_t interval_in_seconds = 2;

uint8_t rxBuffer[5] = {0};
char txBuffer[256];


PWM_Handle_TypeDef PWM1_CH1={
		.Timer = &htim1,
		.Channel = TIM_CHANNEL_1,
		.Duty = 50.0f
};

SWV_TypeDef swv={
		.reference = 35.0f,
		.measurement = 0.0f,
		.control = 50.0f
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//void UART2_SendString(char* str) {
//    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        rxBuffer[sizeof(rxBuffer) - 1] = '\0';  // Ensure the buffer is null-terminated
        char prefix = rxBuffer[0];              // The first character indicates the command type (P or T)
        char data[4] = {0};                     // Array to store numeric data

        // Extract numeric data after the prefix
        strncpy(data, (char*)rxBuffer + 1, 3);  // Copy the 3 characters following the prefix
        data[3] = '\0';                         // Properly terminate the string

        char* endPtr;
        float value = strtol(data, &endPtr, 10); // Convert the numeric value
        value = value / 10.0;
        if (*endPtr == '\0') // Check if the conversion is valid
        {
            if (prefix == 'P' && value >= 0 && value <= 100)  // PWM command
            {
                PWM_WriteDuty(&PWM1_CH1,  value);    // Apply the PWM command

            }
            else if (prefix == 'T' && value >= 0 && value <= 100) // Temperature command
            {
                setpoint = value;  // Divide by 10 to get the temperature in °C
                swv.reference = value;
            }
        }

        // Reactivate UART reception
        HAL_UART_Receive_IT(&huart2, rxBuffer, sizeof(rxBuffer) - 1);
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


  //----------- INITIALISATION -----------//
  HAL_UART_Receive_IT(&huart2, rxBuffer, sizeof(rxBuffer)-1);

  PWM_Init(&PWM1_CH1);

  PID_Init(&hpid1);

  sensirion_i2c_init();
  scd_Setup();
  //----------- ------------- -----------//


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  float co2_ppm = 0.0f;
	  float temperature = 0.0f;
	  float relative_humidity = 0.0f;

	  int8_t result = scd_WaitForAndReadSensorData(
			  interval_in_seconds,
			  &co2_ppm, &temperature,
			  &relative_humidity);

	  if (result != 0) {
		  printf("Error: Failed to retrieve sensor data. Retrying...\n");
		  HAL_Delay(interval_in_seconds*1000); 				// Wait before retrying
	      continue;
	  }
	  //----------- PID COMPUTING -----------//

	  duty = PID_GetOutput(&hpid1, setpoint, temperature);	// Compute the new PWM value
	  PWM_WriteDuty(&PWM1_CH1, duty);						// Set the new PWM

	  //----------- ------------- -----------//

	  swv.control = duty;
	  swv.measurement = temperature;

	  HAL_Delay(10);

	  sprintf(txBuffer,"Duty : %0.2f, "
			  "Set point [degC] : %0.2f, "
			  "Current [degC] : %0.2f\r\n",
			  swv.control, swv.reference, swv.measurement
	   );
	     UART2_SendString(txBuffer);

	  HAL_Delay(interval_in_seconds*1000);					// Wait for 2s


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  scd30_stop_periodic_measurement();
  return 0;
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
