#ifndef __COLORS_H
#define __COLORS_H
#include <stdint.h>
uint8_t rgb888torgb332(const uint8_t red, const uint8_t green, const uint8_t blue);
#define rgb332 rgb888torgb332

#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define BLACK 0x0000
#define WHITE 0xffff
#define GRAY 0x8c51
#define YELLOW 0xFFE0
#define CYAN 0x07FF
#define PURPLE 0xF81F
#define LIME 0x0f0f

/*#define RED rgb332(0xff, 0x00, 0x00)
#define GREEN rgb332(0xff 0xff, 0x00)
#define BLUE rgb332(0x00, 0x00, 0xff)
#define BLACK 0
#define WHITE 0xff
#define GRAY rgb332(0x77, 0x77, 0x77)
#define YELLOW rgb332(0xff, 0xff, 0x00)
#define CYAN rgb332(0x00, 0xff, 0xff)
#define PURPLE rgb332(0xff, 0x00, 0xff)
#define LIME rgb332(0x40, 0xff, 0xff)*/
#define LIGHTGRAY rgb332(0xa9, 0xa9, 0xa9)
#endif