#ifndef matriz_w
#define matriz_w

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
typedef struct {
    uint8_t G, R, B;
} pixel_t;
typedef pixel_t npLED_t;

// Declaração de variáveis globais
extern npLED_t leds[LED_COUNT];
extern PIO np_pio;
extern uint sm;

// Funções de inicialização e controle dos LEDs
void npInit(uint pin);
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
void npClear(void);
void npWrite(void);
int getIndex(int x, int y);
void brightness(int matriz[5][5][3]);

// Funções para exibição de números
void number_0(void);
void number_1(void);
void number_2(void);
void number_3(void);
void number_4(void);
void number_5(void);
void number_6(void);
void number_7(void);
void number_8(void);
void number_9(void);

#endif 
