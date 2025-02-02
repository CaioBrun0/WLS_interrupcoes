# LED Matrix Control with Raspberry Pi Pico

## Introduction
Este projeto tem o intuito de testar os conhecimentos dos residentes sobre interrupções e o sistema de debounce. Ele foi projetado para controlar uma matriz de LED 5x5 usando um Raspberry Pi Pico. O sistema usa botões GPIO para percorrer os números (0-9), que são exibidos na matriz de LED usando WS2812B LEDs. O projeto aproveita o PIO (Entrada/Saída Programável) do Pico para controle eficiente de LED.

## Features
- Usa Raspberry Pi Pico para controlar uma matriz de LED 5x5
- Exibe números de 0 a 9 usando matrizes RGB predefinidas
- Dois botões: A e B da BitDogLab, para navegar pelos números
- Implementa um mecanismo de debounce para evitar pressionamentos de botão não intencionais

## Hardware Requirements
- Raspberry Pi Pico W
- BitDogLab

## Software Requirements
- Raspberry Pi Pico SDK
- C/C++ compiler (e.g., GCC for ARM)
- PIO assembly for WS2812B control

## Pin Configuration
| Component    | GPIO Pin |
|-------------|---------|
| LED Matriz  | 7       |
| Botão A    | 5       |
| Botão B    | 6       |
| Status LED Vermelho  | 13      |

## Code Breakdown
### 1. Header Files
```c
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
```
Essas bibliotecas permitem o controle sobre as funcionalidades GPIO, PIO e clock necessárias para a comunicação com LED.

### 2. Constants and Variables
- `LED_red`: Status LED
- `but_A`, `but_B`: GPIO pins para os botões
- `LED_PIN`: Pino GPIO que controla a matriz de LED WS2812B
- `LED_COUNT`: Numero de LEDS na matriz
- `number_matriz`: Rastreia o número exibido no momento
- `debounce_time_ms`: Atraso de debounce para evitar acionamentos de botões falsos
- `digits[10][5][5][3]`: Armazena valores RGB para exibir números de 0 a 9

### 3. Debounce Mechanism
O programa usa um atraso de debounce ('debounce_time_ms = 250') para evitar pressionamentos não intencionais de vários botões.

### 4. Number Representation
Os números são armazenados em uma matriz 3D onde:
- Cada número é representado como uma matriz 5x5.
- Cada LED tem um trigêmeo RGB (por exemplo, '{20, 20, 20}' para um pixel iluminado, '{0, 0, 0}' para pixels desligados).

## How It Works
1. O Pico inicializa os pinos GPIO e configura a matriz de LED.
2. O sistema aguarda o pressionamento de botões ('but_A' ou 'but_B') para alterar o número exibido.
3. A matriz de LED é atualizada para mostrar o número correspondente.

## Compilation & Uploading
1. Configure o Raspberry Pi Pico SDK em seu sistema.
2. Compile o código usando:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Carregue o arquivo '.uf2' gerado para o Pico arrastando-o para o armazenamento USB montado.

## Future Improvements
- Adicione mais efeitos visuais (por exemplo, transições de fade)
- Suporte para padrões ou símbolos adicionais
- Implemente comunicação serial para controle remoto

## Author
Caio Bruno Santos Matos de Oliveira

## License
Este projeto é de código aberto e licenciado sob a licença do MIT.
