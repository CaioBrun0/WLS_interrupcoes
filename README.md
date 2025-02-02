# Interrupções em um contador na Raspberry Pi Pico

## Introdução
Este projeto tem o intuito de testar os conhecimentos dos residentes sobre interrupções e o sistema de debounce. Ele foi projetado para controlar um contador representado em uma matriz de LED 5x5 usando um Raspberry Pi Pico enquanto um LED vermelho pisca 5 vezes por segundo. O sistema usa botões GPIO para percorrer os números (0-9), que são exibidos na matriz de LED usando WS2812B LEDs. O projeto aproveita o PIO (Entrada/Saída Programável) do Pico para controle eficiente de LED.

## Features
- Usa Raspberry Pi Pico para controlar uma matriz de LED 5x5
- Exibe números de 0 a 9 usando matrizes RGB predefinidas
- Dois botões: A e B da BitDogLab, para navegar pelos números
- Implementa um mecanismo de debounce para evitar pressionamentos de botão não intencionais
- Implementa macanismo de interrupções dentro da função principal

## Requerimento de Hardware
- Raspberry Pi Pico W
- BitDogLab

## Requerimento de Software
- Raspberry Pi Pico SDK
- C/C++ compiler (e.g., GCC for ARM)
- PIO assembly for WS2812B control

## Configurações do Pin
| Componentes    | GPIO Pin |
|-------------|---------|
| LED Matriz  | 7       |
| Botão A    | 5       |
| Botão B    | 6       |
| Status LED Vermelho  | 13      |

## Detalhamento do código
### 1. Arquivos de cabeçalho
```c
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
```
Essas bibliotecas permitem o controle sobre as funcionalidades GPIO, PIO e clock necessárias para a comunicação com LED.

### 2. Constantos e Variavéis
- `LED_red`: Status LED
- `but_A`, `but_B`: GPIO pins para os botões
- `LED_PIN`: Pino GPIO que controla a matriz de LED WS2812B
- `LED_COUNT`: Numero de LEDS na matriz
- `number_matriz`: Rastreia o número exibido no momento
- `debounce_time_ms`: Atraso de debounce para evitar acionamentos de botões falsos
- `digits[10][5][5][3]`: Armazena valores RGB para exibir números de 0 a 9
- `button_a_pressed`: Variavél booleana para ver se o botão A foi pressionado
- `button_b_pressed`: Variavél booleana para ver se o botão B foi pressionado

### 3. Mecanismo de Debounce
O programa usa um atraso de debounce ('debounce_time_ms = 250') para evitar pressionamentos não intencionais de vários botões.

### 4. Representação dos números
Os números são armazenados em uma matriz 3D onde:
- Cada número é representado como uma matriz 5x5.
- Cada LED tem um trigêmeo RGB (por exemplo, '{20, 20, 20}' para um pixel iluminado, '{0, 0, 0}' para pixels desligados).

## Como funciona
1. O Pico inicializa os pinos GPIO e configura a matriz de LED.
2. O sistema aguarda o pressionamento de botões ('but_A' ou 'but_B') para alterar o número exibido.
3. A matriz de LED é atualizada para mostrar o número correspondente.

## Como as Interrupções Funcionam

As interrupções são utilizadas para detectar o pressionamento dos botões but_A e but_B de maneira eficiente, sem a necessidade de polling constante. A seguir, explicamos como elas estão implementadas:

Configuração dos botões como entrada

Os pinos dos botões são configurados como entradas pull-down para evitar estados indefinidos.

Registro da interrupção

As interrupções são configuradas para serem acionadas na borda de subida (quando o botão é pressionado).

Função de tratamento da interrupção

Quando um botão é pressionado, a função de callback é executada.

Um tempo de debounce é aplicado para evitar leituras incorretas causadas por ruídos elétricos.

A variável global correspondente ao botão é atualizada para indicar que um evento ocorreu.

Exemplo de Configuração das Interrupções

void button_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_interrupt_time, now) > debounce_time_ms * 1000) {
        last_interrupt_time = now;
        if (gpio == but_A) {
            button_a_pressed = true;
        } else if (gpio == but_B) {
            button_b_pressed = true;
        }
    }
}

Configuração dos Pinos para Interrupção

gpio_set_irq_enabled_with_callback(but_A, GPIO_IRQ_EDGE_RISE, true, &button_callback);
gpio_set_irq_enabled_with_callback(but_B, GPIO_IRQ_EDGE_RISE, true, &button_callback);

Com essa abordagem, evitamos o uso de loops constantes para verificar os botões, economizando processamento e energia.

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
