#include <stdio.h>
#include "pico/stdlib.h"

#define LED_red 13


int main(){
    gpio_init(LED_red);                 // Inicializa o pino do LED
    gpio_set_dir(LED_red, GPIO_OUT);    // Configura o pino como saída

    stdio_init_all();

    while (true) {
        gpio_put(LED_red, 1);
        sleep_ms(100);
        gpio_put(LED_red, 0);
        sleep_ms(100);
    }
}
