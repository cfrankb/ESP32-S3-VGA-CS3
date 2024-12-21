#include "colors.h"

// RGB 565
uint16_t rgb888torgb565(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    const uint16_t b = (blue >> 3) & 0x1f;
    const uint16_t g = ((green >> 2) & 0x3f) << 5;
    const uint16_t r = ((red >> 3) & 0x1f) << 11;
    return (uint16_t)(r | g | b);
}

uint16_t swapRedBlue(const uint16_t c)
{
    constexpr const uint16_t greenFilter = 0x20 + 0x40 +
                                           0x80 + 0x100 +
                                           0x200 + 0x400;
    return (c << 11) | (c >> 11) | (c & greenFilter);
}
