/**
 * @file    delay.c
 * @brief   none
 * @version 0.1.0
 * @author  
 * @date    
 */

#include "delay.h"
#include "stdint.h"
#include "stm32wbxx_hal.h"

void bsp_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}
