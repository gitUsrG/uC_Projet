/*
 * scd30_app.h
 *
 *  Created on: Jan 24, 2025
 *      Author: gabyb
 */

#ifndef INC_SCD30_APP_H_
#define INC_SCD30_APP_H_

#include "usart.h"

#include "scd30.h"

#include <stdio.h> /* printf */
#include <string.h>



extern uint16_t interval_in_seconds;
extern char txBuffer[256];

void UART2_SendString(char* str);


void scd_Setup(void);

int8_t scd_WaitForAndReadSensorData(
		uint32_t interval_in_seconds,
        float* co2_ppm,
        float* temperature,
        float* relative_humidity);



#endif /* INC_SCD30_APP_H_ */
