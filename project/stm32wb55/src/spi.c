/**
* @file    spi.c
* @brief   none
* @version 0.1.0
* @author  Your name here
* @date    2026-04-20
*/

#include "stm32wbxx_hal.h"
#include "spi.h"
#include "stm32wbxx_hal_spi.h"

/*
*   global SPI_Handle
*/
SPI_HandleTypeDef hspi1;

uint8_t spi_init(void) {
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES; 
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;   
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;       
    hspi1.Init.NSS = SPI_NSS_SOFT;              
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;                                                                  ; 
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;      
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        return 1;
    }
    return 0;
}

uint8_t spi_deinit(void) {
    if (HAL_SPI_DeInit(&hspi1) != HAL_OK)
        return 1;

    return 0;
}

uint8_t spi_write(uint8_t *buf, uint16_t len) {
    if (HAL_SPI_Transmit(&hspi1, buf, len, HAL_MAX_DELAY) != HAL_OK)
        return 1;

    return 0;
}
