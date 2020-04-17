#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>

#include "colors.h"
#include "pwm.h"

void blink (color_t color) {
    static bool rising = true;
    static int16_t duty_cycle = 0;
    color_t output;
    
    output.red = (uint16_t)color.red * duty_cycle / 255;
    output.green = (uint16_t)color.green * duty_cycle / 255;
    output.blue = (uint16_t)color.blue * duty_cycle / 255;

    set_all_PWM(output);

    if (rising) duty_cycle++;
    else duty_cycle--;

    if (duty_cycle == 255 || !duty_cycle) rising = !rising;
}

void cycle_blink (color_t colors[], uint8_t len) {
    static bool rising = true;
    color_t output;
    static uint8_t duty_cycle = 0;
    static uint8_t i = 0;

    if (i >= len) i = 0;
    
    output.red = (uint16_t)colors[i].red * duty_cycle / 255;
    output.green = (uint16_t)colors[i].green * duty_cycle / 255;
    output.blue = (uint16_t)colors[i].blue * duty_cycle / 255;

    set_all_PWM(output);

    if (rising) duty_cycle++;
    else duty_cycle--;

    if (duty_cycle == 255) {
        rising = 0;
    } else if (!duty_cycle) {
        rising = 1;
        i++;
    }
}

void wave () {
    static uint8_t state = 0;
    static color_t output = {0, 0, 0};

    switch (state) {
    case 0:
        if (!output.blue) state++;
        else output.blue--;
        break;

    case 1:
        if (output.red == 255) state++;
        else output.red++;   
        break;

    case 2:
        if (!output.green) state++;
        else output.green--;
        break;
    
    case 3:
        if (output.blue == 255) state++;
        else output.blue++;
        break;

    case 4:
        if (!output.red) state++;
        else output.red--;
        break;
    
    case 5:
        if (output.green == 255) state++;
        else output.green++;
        break;
    
    default:
        state = 0;
        return;
    }

    set_all_PWM(output);
}

static void single_color(color_t color) {
    set_all_PWM(color);
}

#endif