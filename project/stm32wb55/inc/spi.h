/**
 * @file spi.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-04-20
 */

#ifndef SPI_H
#define SPI_H

#include "stdint.h"

uint8_t spi_init(void);
uint8_t spi_deinit(void);
uint8_t spi_write(uint8_t *buf, uint16_t len);

#endif // SPI_H
