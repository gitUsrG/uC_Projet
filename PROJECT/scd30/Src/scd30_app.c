/*
 * scd30_app.c
 *
 *  Created on: Jan 24, 2025
 *      Author: gabyb
 */
/* USER CODE BEGIN Includes */

#include "scd30_app.h"

/* USER CODE END Includes */

/* USER CODE BEGIN V */

/* USER CODE END V */

void UART2_SendString(char* str) {
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}



void scd_Setup(void){

    while (scd30_probe() != NO_ERROR) {
    	UART2_SendString("SCD30 sensor probing failed\n");
        sensirion_sleep_usec(1000000u);
    }
    UART2_SendString("SCD30 sensor probing successful\n");

    scd30_set_measurement_interval(interval_in_seconds);
    sensirion_sleep_usec(20000u);
    scd30_start_periodic_measurement(0);
}

int8_t scd_WaitForAndReadSensorData(uint32_t interval_in_seconds,
                             float* co2_ppm,
                             float* temperature,
                             float* relative_humidity) {
    uint16_t data_ready = 0;
    uint16_t timeout = 0;
    int8_t err;

    /* Poll data_ready flag until data is available. Allow 20% more than
     * the measurement interval to account for clock imprecision of the sensor.
     */
    for (timeout = 0; (100000 * timeout) < (interval_in_seconds * 1200000); ++timeout) {
        err = scd30_get_data_ready(&data_ready);
        if (err != NO_ERROR) {
        	sprintf(txBuffer,"Error reading data_ready flag: %i\n", err);
        	UART2_SendString(txBuffer);
            return err;  // Return error code
        }
        if (data_ready) {
            break;  // Data is ready
        }
        sensirion_sleep_usec(100000);  // Wait for 100 ms
    }

    if (!data_ready) {
    	UART2_SendString("Timeout waiting for data_ready flag\n");
        return -1;  // Timeout error
    }

    /* Read CO2, temperature, and relative humidity */
    err = scd30_read_measurement(co2_ppm, temperature, relative_humidity);
    if (err != NO_ERROR) {
    	UART2_SendString("Error reading measurement\n");
        return err;  // Return error code
    }

    sprintf(txBuffer,"Measured CO2 concentration: %0.2f ppm, "
           "Measured temperature: %0.2f °C, "
           "Measured humidity: %0.2f %%RH\n",
           *co2_ppm, *temperature, *relative_humidity);
    UART2_SendString(txBuffer);
    return 0;  // Success
}

