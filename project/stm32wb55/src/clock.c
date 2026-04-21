/**
 * @file    clock.c
 * @brief   none
 * @version 0.1.0
 * @author  
 * @date    
 */

#include "clock.h"
#include "stdint.h"
#include "stm32wbxx_hal.h"

uint8_t clock_init(void) {
  
  /*
  * clock configuration can be generated using CubeMX Software
  */
  __HAL_RCC_SPI1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_LPTIM1_CLK_ENABLE();


  return 0;
}
