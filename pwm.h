#ifndef PWM_H
#define PWM_H

#ifndef __AVR_ATtiny85__
#define __AVR_ATtiny85__
#endif

#include <avr/io.h>

#include "colors.h"

typedef enum {
    RED, 
    GREEN,
    BLUE
} channel_t;

void set_PWM(channel_t channel, uint8_t duty_cycle) {
    switch (channel) {
        case RED:
        OCR0A = 255-duty_cycle;
        break;

        case GREEN:
        OCR0B = 255-duty_cycle;
        break;

        case BLUE:
        OCR1B = 255-duty_cycle;
        break;

    }
}

void set_all_PWM(color_t color) {
    set_PWM(RED, color.red);
    set_PWM(GREEN, color.green);
    set_PWM(BLUE, color.blue);
}

#endif