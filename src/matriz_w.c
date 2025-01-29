#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"


// Definição do número de LEDs e pino.
#define ROWS 4
#define COLS 4
#define LED_COUNT 25
#define LED_PIN 7


// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin) {

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}


void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

//Limpa o buffer
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

//Escreve os dados no buffer
void npWrite() {
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y) {
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0) {
        return 24-(y * 5 + x); // Linha par (esquerda para direita).
    } else {
        return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}


//função para ajustar a luminosidade do led e mandar para escrever no buffer
void brightness(int matriz[5][5][3]){
    float fator = 0.6;

    // Ajustar cada valor da matriz
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Ajustar os valores de vermelho, verde e azul
            matriz[i][j][0] = (int)(matriz[i][j][0] * fator); // Vermelho
            matriz[i][j][1] = (int)(matriz[i][j][1] * fator); // Verde
            matriz[i][j][2] = (int)(matriz[i][j][2] * fator); // Azul
        }
    }

    // Atualizar os LEDs com os valores ajustados
    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz[coluna][linha][0], matriz[coluna][linha][1], matriz[coluna][linha][2]);
        }
    }

    npWrite();

}


void number_0(){
     int number_0[5][5][3] = {
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}}
    };

    brightness(number_0);

}

void number_1(){
    int number_1[5][5][3] = {
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}}
    };

    brightness(number_1);
}

void number_2(){
    int number_2[5][5][3] = {
   {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_2);
}

void number_3(){
    int number_3[5][5][3] = {
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_3);
}

void number_4(){
    int number_4[5][5][3] = {
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}}
  };

  brightness(number_4);
}

void number_5(){
    int number_5[5][5][3] = {
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_5);
}

void number_6(){
    int number_6[5][5][3] = {
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_6);
}

void number_7(){
    int number_7[5][5][3] = {
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };

  brightness(number_7);
}

void number_8(){
    int number_8[5][5][3] = {
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_8);
}

void number_9(){
    int number_9[5][5][3] = {
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
  };

  brightness(number_9);
}