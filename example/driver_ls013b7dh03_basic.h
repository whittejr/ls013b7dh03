/**
 * @file driver_ls013b7dh03_basic.h
 * @brief  High-level basic example for LS013B7DH03
 * @version 1.0.0
 * @author Alessandro Davi
 * @date 2026-04-21
 */

#ifndef DRIVER_LS013B7DH03_BASIC_H
#define DRIVER_LS013B7DH03_BASIC_H

#include "driver_ls013b7dh03_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief  Initialize the display for basic use
 * @param  fb_pointer pointer to a 2048-byte buffer
 * @return 0: success, 1: error
 */
uint8_t ls013b7dh03_basic_init(const uint8_t *fb_pointer);

/**
 * @brief  Deinitialize the display
 * @return 0: success, 1: error
 */
uint8_t ls013b7dh03_basic_deinit(void);

/**
 * @brief  Clear the screen
 * @return 0: success, 1: error
 */
uint8_t ls013b7dh03_basic_clear(void);

/**
 * @brief  Send the buffer to the screen
 * @return 0: success, 1: error
 */
uint8_t ls013b7dh03_basic_refresh(void);

#ifdef __cplusplus
}
#endif

#endif
