/**
 * @file ls013b7dh03_interface.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-01-27
 */

#ifndef LS013B7DH03_INTERFACE_H
#define LS013B7DH03_INTERFACE_H

#include <stdint.h>


/*
* @brief       interface spi bus init  
* @return      status code
*            - 0 success
*            - 1 spi init failed
* @note       
*/
uint8_t ls013b7dh03_interface_spi_init(void);

/*
* @brief       interface spi bus deinit  
* @return      status code
*            - 0 success
*            - 1 spi deinit failed
* @note       
*/
uint8_t ls013b7dh03_interface_spi_deinit(void);

/*
* @brief       interface spi bus write
* @param[in]   *buf pointer to a data buffer
* @param[in]   len length of a data buffer
* @return      status code
*            - 0 success
*            - 1 write failed
* @note       
*/
uint8_t ls013b7dh03_interface_spi_write(uint8_t *buf, uint16_t len);

/*
* @brief       provides chip select control
* @param[in]   state of 0 or 1 to select the chip
* @note        none
*/
void ls013b7dh03_interface_cs_control(uint8_t state);

/*
* @brief       adds delay 
* @param[in]   uint32_t value for delay in ms
* @note        none
*/
void ls013b7dh03_interface_delay_ms(uint32_t ms);


#endif // LS013B7DH03_INTERFACE_H
