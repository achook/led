#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "leds.h"
#include "colors.h"

static void set_registers() {
    DDRB &= ~_BV(PB2) & ~_BV(PB3); // Inputs for switches
	PORTB |= _BV(PB2) | _BV(PB3); // Pull-ups
	
	TCCR0A |= _BV(COM0A1) | _BV(COM0A0) | _BV(COM0B1) | _BV(COM0B0); // Inverted output, Timer 0
	TCCR0A |= _BV(WGM00) | _BV(WGM01); // Fast PWM 8-bit
	TCCR0B |= _BV(CS01); // Fast PWM 8-bit, prescaler 8
	
	GTCCR |= _BV(COM1B1) | _BV(COM1B0); /// Inverted output, Timer 1
    GTCCR |= _BV(PWM1B); // PWM
	TCCR1 |= _BV(CS12); // Prescaler 8
    TCCR1 |= _BV(COM1A0); // COM1A0 needs to be set becaus of the hardware bug
	
	DDRB |= _BV(PB0) | _BV(PB1) | _BV(PB4); // High state for PWM on PORT B
}

int main(void) {
    uint8_t counters[2];
    uint8_t old_button_state = PINB & (_BV(PB2) | _BV(PB3));
	uint8_t button_state;

	uint8_t led_parameter = 0;
	uint8_t led_mode = 0;
    
    uint8_t mask;

	set_registers();

	while (1) {
		if (!counters[0]) {
            mask = _BV(PB2);
			button_state = PINB & mask;

			if( ((button_state^old_button_state) & mask) && !(button_state & mask) ) {
				led_mode++;
				counters[0] = 25;
			}

			old_button_state &= ~mask;
			old_button_state |= button_state;
		}

		if (!counters[1]) {
            mask = _BV(PB3);
			button_state = PINB & mask;

			if( ((button_state^old_button_state) & mask ) && !(button_state & mask) ) {
				led_parameter++;
				counters[1] = 25;
			}
            
			old_button_state &= ~mask;
			old_button_state |= button_state;
		}

		for (uint8_t c = 0; c < 2; c++) {
			if (counters[c]) counters[c]--;
		}

        switch (led_mode) {
            case 0:
                wave();
                break;

            case 1:
                if (led_parameter >= COLORS_LENGTH) led_parameter = 0;
                single_color(COLORS[led_parameter]);
                break;

            case 2:
                if (led_parameter >= COLORS_LENGTH) led_parameter = 0;
                blink(COLORS[led_parameter]);
                break;

            case 3:
                cycle_blink(COLORS, COLORS_LENGTH);
                break;
            
            default:
                led_mode = 0;
                break;
        }

		_delay_ms(10);
	}

    return 0;
}