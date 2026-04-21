/**
 * @file driver_ls013b7dh03_test.c
 * @brief  Funcional tests for ls013b7dh03
 * @version 1.0.0
 * @author Alessandro Davi
 * @date 2026-04-21
 */

#include "driver_ls013b7dh03.h"
#include "driver_ls013b7dh03_interface.h"

/**
 * @brief  Run a simple display test
 * @note   This will clear the screen and send a pattern if buffer is provided
 * @return 0: success, 1: error
 */
uint8_t ls013b7dh03_test(const uint8_t *fb_pointer) {
    ls013b7dh03_handle_t handle;
    
    // Link
    handle.spi_write = ls013b7dh03_interface_spi_write;
    handle.cs_control = ls013b7dh03_interface_cs_control;
    handle.delay_ms = ls013b7dh03_interface_delay_ms;
    handle.buffer = fb_pointer;

    // 1. Init
    if (ls013b7dh03_init(&handle) != 0) return 1;

    // 2. Hardware Clear
    if (ls013b7dh03_clear(&handle) != 0) return 1;
    
    handle.delay_ms(500);

    // 3. Refresh (if buffer exists)
    if (handle.buffer != NULL) {
        if (ls013b7dh03_refresh(&handle) != 0) return 1;
    }

    return 0;
}
