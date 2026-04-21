/**
* @file    gpio.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-04-21
*/

#include "gpio.h"
#include "board_config.h"
#include "stm32wbxx_hal.h"

uint8_t gpio_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    LPTIM_HandleTypeDef hlptim1 = {0};

    // CS, DISP as output
    HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISP_ON_PORT, DISP_ON_PIN, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = DISP_CS_PIN | DISP_ON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // spi configuration
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1; // Alternativa correta pro SPI1 no WB55
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // enables display (disp = high)
    HAL_GPIO_WritePin(DISP_ON_PORT, DISP_ON_PIN, GPIO_PIN_SET);

    // pwm init
    GPIO_InitStruct.Pin = DISP_EXTCOM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // ATENÇÃO: AF1 costuma ser o padrão para o LPTIM1 (ex: PB2, PA14, PC1). 
    // Confirme no datasheet do STM32WB55 se o seu pino específico usa o AF1.
    GPIO_InitStruct.Alternate = GPIO_AF1_LPTIM1; 
    HAL_GPIO_Init(DISP_EXTCOM_PORT, &GPIO_InitStruct);

    hlptim1.Instance = LPTIM1;
  
    hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC; 
    hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV4; 
    hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    hlptim1.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
    hlptim1.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;

    if (HAL_LPTIM_Init(&hlptim1) != HAL_OK) {
        return 1;
    }

    /* ==========================================================
     * 5. turning pwm on
     * ========================================================== */
    // period = 16666, pulse (Duty 50%) = 8333
    if (HAL_LPTIM_PWM_Start(&hlptim1, 16666, 8333) != HAL_OK) {
        return 1;
    }

    return 0;
}

void gpio_cs_control(uint8_t state) {
    if (state)
        HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_RESET);
}
