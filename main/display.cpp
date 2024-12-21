#include "display.h"
#include <algorithm>
#include <esp_log.h>

extern uint8_t bitfont_bin;
static const char TAG[]{"display"};

CDisplay::CDisplay(uint8_t *buf, int width, int height)
{
    // ESP_LOGI(TAG, "Building Display Wrapper");
    m_buf = buf;
    m_width = width;
    m_height = height;
};

void CDisplay::drawTile32(uint16_t x, uint16_t y, uint8_t *tile) const
{
    // ESP_LOGI(TAG, "Drawing tile at: %d %d %p", x, y, tile);
    uint8_t *o = m_buf + x + y * m_width;
    uint32_t *p32 = reinterpret_cast<uint32_t *>(tile);
    for (int yy = 0; yy < 16; ++yy)
    {
        uint32_t *d32 = reinterpret_cast<uint32_t *>(o);
        d32[0] = p32[0];
        d32[1] = p32[1];
        d32[2] = p32[2];
        d32[3] = p32[3];
        o += m_width;
        p32 += 4;
    }
}

void CDisplay::drawTile(uint16_t x, uint16_t y, uint8_t *tile, bool alpha) const
{
    // ESP_LOGI(TAG, "Drawing tile at: %d %d %p", x, y, tile);
    uint8_t *d = m_buf + x + y * m_width;
    int i = 0;
    for (int yy = 0; yy < 16; ++yy)
    {
        for (int xx = 0; xx < 16; ++xx)
        {
            d[xx + yy * m_width] = tile[i++];
        }
    }
}

void CDisplay::fill(const uint8_t color) const
{
    ESP_LOGI(TAG, "Display Fill Display %d x %d", m_width, m_height);
    assert(m_buf != nullptr);
    for (int i = 0; i < m_width * m_height; ++i)
    {
        m_buf[i] = color;
    }
}

void CDisplay::drawFont(const int x, const int y, const char *s, uint8_t color) const
{
    // ESP_LOGI(TAG, "Display Draw Font at (%d,%d): %s", x, y, s);
    uint8_t *font = &bitfont_bin;
    for (int j = 0; s[j]; ++j)
    {
        int u = s[j] < 127 ? std::max(s[j] - 32, 0) : 0;
        uint8_t *o = m_buf + x + y * m_width + 8 * j;
        for (int yy = 0; yy < 8; ++yy)
        {
            uint8_t data = font[8 * u + yy];
            for (int xx = 0; xx < 8; ++xx)
            {
                o[xx] = data & 1 ? color : 0;
                data = data >> 1;
            }
            o += m_width;
        }
    }
}

void CDisplay::drawRect(const Rect &rect, const uint8_t color, const bool fill) const
{
    uint8_t *buf = m_buf + rect.x + rect.y * m_width;
    if (fill)
    {
        for (int y = 0; y < rect.height; ++y)
        {
            for (int x = 0; x < rect.width; ++x)
            {
                buf[x] = color;
            }
            buf += m_width;
        }
    }
    else
    {
        for (int y = 0; y < rect.height; ++y)
        {
            for (int x = 0; x < rect.width; ++x)
            {
                if (x == 0 || y == 0 || x == rect.width - 1 || y == rect.height - 1)
                {
                    buf[x] = color;
                }
            }
            buf += m_width;
        }
    }
}
