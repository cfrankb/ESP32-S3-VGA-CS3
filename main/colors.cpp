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
    // constexpr const uint16_t redFilter = 0x1f;
    //    constexpr const uint16_t blueFilter = 0x1f;
    constexpr const uint16_t greenFilter = 0x20 + 0x40 +
                                           0x80 + 0x100 +
                                           0x200 + 0x400;
    return (c << 11) | (c >> 11) | (c & greenFilter);
}

// RGB 332
uint8_t rgb888torgb332(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    // bit
    // 1     low red
    // 2     low green
    // 3     low blue
    // 4     high red
    // 5     high green
    // 6     high blue
    // 7     mid red
    // 8     mid green

    /*
        const uint8_t b = ((blue & 0xf0) ? 0x20 : 0) |  // high
                          ((blue & 0x0f) ? 0x04 : 0);   // low
        const uint8_t g = ((green & 0xc0) ? 0x10 : 0) | // high
                          ((green & 0x70) ? 0x80 : 0) | // mid
                          ((green & 0x0f) ? 0x02 : 0);  // low
        const uint8_t r = ((red & 0xc0) ? 0x08 : 0) |   // high
                          ((red & 0x70) ? 0x40 : 0) |   // mid
                          ((red & 0x0f) ? 0x01 : 0);    // low
    */

    const uint8_t r = ((red & 0x80) ? 0x08 : 0) |   // high
                      ((red & 0x70) ? 0x01 : 0) |   // mid
                      ((red & 0x0f) ? 0x40 : 0);    // low
    const uint8_t g = ((green & 0xc0) ? 0x10 : 0) | // high
                      ((green & 0x70) ? 0x02 : 0) | // mid
                      ((green & 0x0f) ? 0x80 : 0);  // low
    const uint8_t b = ((blue & 0x80) ? 0x20 : 0) |  // high
                      ((blue & 0x78) ? 0x04 : 0);   // mid

    return (uint8_t)(r | g | b);
}
