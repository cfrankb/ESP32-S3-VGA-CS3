#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <inttypes.h>

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} Rect;

class CDisplay
{
public:
    CDisplay(uint8_t *buf, int width, int height);
    ~CDisplay() {};
    void drawTile(uint16_t x, uint16_t y, uint8_t *tile, bool alpha = false) const;
    void drawTile32(uint16_t x, uint16_t y, uint8_t *tile) const;
    void fill(const uint8_t color) const;
    void drawFont(const int x, const int y, const char *s, uint8_t color) const;
    void drawRect(const Rect &rect, const uint8_t color, const bool fill = true) const;

protected:
    uint8_t *m_buf = nullptr;
    int m_width;
    int m_height;
};

#endif