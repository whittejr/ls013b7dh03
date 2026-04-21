/**
 * @file gpio.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-04-21
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

uint8_t gpio_init(void);
void gpio_cs_control(uint8_t state);

#endif // GPIO_H
