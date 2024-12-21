#pragma once
#include <stdint.h>
uint16_t swapRedBlue(const uint16_t c);
uint16_t rgb888torgb565(const uint8_t red, const uint8_t green, const uint8_t blue);

#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define BLACK 0x0000
#define WHITE 0xffff
#define GRAY swapRedBlue(0x8c51)
#define YELLOW swapRedBlue(0xFFE0)
#define CYAN 0x07FF
#define PURPLE 0xF81F
#define LIME 0x0f0f
#define LIGHTGRAY rgb888torgb565(0xa9, 0xa9, 0xa9)