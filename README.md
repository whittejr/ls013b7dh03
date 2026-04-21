# LS013B7DH03 Display Driver

Driver modular e independente de hardware para o display Sharp Memory LCD LS013B7DH03 (128x128).

## Estrutura do Projeto
- `/src`: Core do driver (lógica de protocolo).
- `/interface`: Arquivos para você mapear os comandos para o seu MCU (SPI, GPIO, Delay).
- `/example`: Exemplos de uso simplificado (Basic API).
- `/extension`: Biblioteca opcional de GFX (Desenho de pixels, fontes, bitmaps).
- `/test`: Código para teste de funcionalidades.

## Como Usar

### 1. Implementar a Interface
No arquivo `driver_ls013b7dh03_interface.c`, conecte as funções de SPI e GPIO do seu hardware.

### 2. Fluxo Básico
```c
#include "driver_ls013b7dh03_basic.h"

uint8_t frame_buffer[2048]; // Buffer de RAM para a imagem

void main() {
    // Inicializa o driver apontando para o seu buffer
    ls013b7dh03_basic_init(frame_buffer);

    // Limpa o vidro do display
    ls013b7dh03_basic_clear();

    // ... manipule os bits no seu frame_buffer ...

    // Envia o buffer para a tela
    ls013b7dh03_basic_refresh();
}
```
