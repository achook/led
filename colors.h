#ifndef COLORS_H
#define COLORS_H

#include <avr/io.h>

#define COLORS_LENGTH 7

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

color_t COLORS[COLORS_LENGTH] = {
    {255, 0, 0},
    {255, 255, 0},
    {0, 255, 0},
    {0, 255, 255},
    {0, 0, 255},
    {255, 0, 255},
    {255, 255, 255}
};

#endif