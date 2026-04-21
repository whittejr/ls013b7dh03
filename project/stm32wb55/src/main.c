/**
* @file    main.c
* @brief   Main file for Sharp Memory LCD testing
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-04-21
*/

#include "main.h"
#include <string.h>
#include "gpio.h"
#include "spi.h"
#include "stm32wbxx_hal.h"
#include "clock.h"
#include "ls013b7dh03.h"
#include "ls013b7dh03_interface.h"
#include "gfx.h"
#include "anim_frames.h" // Necessário para acessar o GIF na Flash

static uint8_t fb_ram[LS013B7_BUFFER_SIZE] = {0};
static gfx_context_t gfx;
static ls013b7dh03_handle_t display_handle;

/* =========================================================================
 * FUNÇÕES DE TESTE DA APLICAÇÃO
 * ========================================================================= */

void app_test_screen(void) {
    // 1. Limpa a RAM (Pinta tudo de branco = 1)
    gfx_clear(&gfx, 1);

    // 2. Desenha um quadrado central de 32x32 preto (0)
    for(uint8_t x = 48; x < 80; x++) {
        for(uint8_t y = 48; y < 80; y++) {
            gfx_draw_pixel(&gfx, x, y, 0); 
        }
    }

    // 3. Escreve um texto usando a lib GFX
    gfx_write_string(&gfx, 45, 10, "TESTE", Font_7x10, 0);

    // 4. Manda o buffer inteiro pra tela
    ls013b7dh03_refresh(&display_handle);
}

void app_play_gif(void) {
    // Loop do GIF 3 vezes
    for (uint8_t loop = 0; loop < 3; loop++) {
        for (uint16_t f = 0; f < ANIM_NUM_FRAMES; f++) {
            
            // Copia o quadro atual direto da Flash para a RAM (fb_ram)
            memcpy(fb_ram, anim_frames[f], LS013B7_BUFFER_SIZE);
            
            // Atualiza a tela com o que tá na RAM
            ls013b7dh03_refresh(&display_handle);
            
            // Delay do FPS (~20 FPS)
            if (display_handle.delay_ms) {
                display_handle.delay_ms(50);
            }
        }
    }
}

void app_test_animation(void) {
    int16_t x = 10, y = 20, dx = 3, dy = 2;
    uint8_t box_size = 12;

    // Limpa a tela antes de começar
    gfx_clear(&gfx, 1);
    ls013b7dh03_refresh(&display_handle);

    // Roda 300 frames da animação
    for (uint16_t frame = 0; frame < 300; frame++) { 
        
        // Pinta a RAM de branco
        gfx_clear(&gfx, 1);

        // Atualiza a posição do quadrado
        x += dx; 
        y += dy;

        // Verifica colisões nas bordas
        if (x <= 0 || x >= (LS013B7_WIDTH - box_size)) dx = -dx;
        if (y <= 1 || y >= (LS013B7_HEIGHT - box_size)) dy = -dy;

        // Desenha o quadrado preto na RAM nova posição
        for(uint8_t i = 0; i < box_size; i++) {
            for(uint8_t j = 0; j < box_size; j++) {
                gfx_draw_pixel(&gfx, x + i, y + j, 0);
            }
        }

        // Manda atualizar apenas o trecho que o quadrado ocupou
        ls013b7dh03_refresh_partial(&display_handle, (uint8_t)y, box_size);

        // Trava em ~60 FPS
        if (display_handle.delay_ms) {
            display_handle.delay_ms(16); 
        }
    }
}

/* =========================================================================
 * MAIN PROGRAM
 * ========================================================================= */

int main(void)
{
    HAL_Init();
    clock_init();
    gpio_init();
    spi_init();
    
    // 1. Inicializa o contexto gráfico na RAM
    gfx_init(&gfx, fb_ram, LS013B7_WIDTH, LS013B7_HEIGHT, 1);

    // 2. Vincula as interfaces físicas ao driver
    DRIVER_LS013B7DH03_LINK_INIT(&display_handle, ls013b7dh03_handle_t);
    DRIVER_LS013B7DH03_LINK_SPI_INIT(&display_handle, ls013b7dh03_interface_spi_init);
    DRIVER_LS013B7DH03_LINK_SPI_DEINIT(&display_handle, ls013b7dh03_interface_spi_deinit);
    DRIVER_LS013B7DH03_LINK_SPI_WRITE_CMD(&display_handle, ls013b7dh03_interface_spi_write);
    DRIVER_LS013B7DH03_LINK_SPI_WRITE_REFRESH(&display_handle, ls013b7dh03_interface_spi_write);
    DRIVER_LS013B7DH03_LINK_CS_CONTROL(&display_handle, ls013b7dh03_interface_cs_control);
    DRIVER_LS013B7DH03_LINK_DELAY_MS(&display_handle, ls013b7dh03_interface_delay_ms);

    // 3. Aponta o Hardware Driver para o mesmo buffer da lib GFX
    display_handle.buffer = fb_ram;

    // 4. Inicializa e limpa a tela fisicamente
    ls013b7dh03_init(&display_handle);
    ls013b7dh03_clear(&display_handle);

    // Um pequeno delay para estabilização de VCOM e cristais líquidos
    if (display_handle.delay_ms) display_handle.delay_ms(100);

    /* --- ROTINA DE TESTES SEQUENCIAIS --- */
    
    app_test_screen();
    if (display_handle.delay_ms) display_handle.delay_ms(2000); // Pausa de 2s para você ver o teste estático
    
    app_play_gif();
    if (display_handle.delay_ms) display_handle.delay_ms(1000); // Pausa de 1s antes de quicar o quadrado
    
    app_test_animation();

    // Quando os testes acabarem, ele entra no loop principal
    while (1)
    {
        // ... Logica final do relógio (leitura de sensor, update de watchface, etc)
    }

    return 0;
}
