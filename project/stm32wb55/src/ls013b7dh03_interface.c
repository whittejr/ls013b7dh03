/**
* @file    ls013b7dh03_interface.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-01-27
*/

#include "stdint.h"
#include "ls013b7dh03_interface.h"
#include "gpio.h"
#include "spi.h"
#include "delay.h"

/**
 * @brief spi init
 */
uint8_t ls013b7dh03_interface_spi_init(void) {
    // mockup init (peripherals being initialized globally in main.c)
    return 0;
}

/**
 * @brief spi deinit
 */
uint8_t ls013b7dh03_interface_spi_deinit(void) {
    return spi_deinit();
    
}

/**
 * @brief spi write
 */
uint8_t ls013b7dh03_interface_spi_write(uint8_t *buf, uint16_t len) {
    return spi_write(buf, len);
}

/**
 * @brief chip select control
 */
void ls013b7dh03_interface_cs_control(uint8_t state) {
    gpio_cs_control(state);
}

/**
 * @brief delay_ms
 */
void ls013b7dh03_interface_delay_ms(uint32_t ms) {
    bsp_delay_ms(ms);
}
