#include "draft.h"
#include <algorithm>
#include <esp_log.h>

extern uint8_t bitfont_bin;
static const char TAG[]{"draft"};

CDraft::CDraft(int width, int height)
{
    // ESP_LOGI(TAG, "Building Display Wrapper");
    m_buf = new uint16_t[width * height];
    m_width = width;
    m_height = height;
};

void CDraft::drawTile32(uint16_t x, uint16_t y, uint16_t *tile) const
{
    // ESP_LOGI(TAG, "Drawing tile at: %d %d %p", x, y, tile);
    uint16_t *o = m_buf + x + y * m_width;
    uint32_t *p32 = reinterpret_cast<uint32_t *>(tile);
    for (int yy = 0; yy < TILE_SIZE; ++yy)
    {
        uint32_t *d32 = reinterpret_cast<uint32_t *>(o);
        d32[0] = p32[0];
        d32[1] = p32[1];
        d32[2] = p32[2];
        d32[3] = p32[3];
        d32[4] = p32[4];
        d32[5] = p32[5];
        d32[6] = p32[6];
        d32[7] = p32[7];
        o += m_width;
        p32 += 8;
    }
}

void CDraft::drawTile(uint16_t x, uint16_t y, uint16_t *tile, bool alpha) const
{
    // ESP_LOGI(TAG, "Drawing tile at: %d %d %p", x, y, tile);
    uint16_t *d = m_buf + x + y * m_width;
    int i = 0;
    for (int yy = 0; yy < TILE_SIZE; ++yy)
    {
        for (int xx = 0; xx < TILE_SIZE; ++xx)
        {
            const auto pixel = tile[i++];
            if (pixel || !alpha)
            {
                d[xx + yy * m_width] = pixel;
            }
        }
    }
}

void CDraft::fill(const uint16_t color) const
{
    ESP_LOGI(TAG, "Fill Buffer %d x %d", m_width, m_height);
    assert(m_buf != nullptr);
    for (int i = 0; i < m_width * m_height; ++i)
    {
        m_buf[i] = color;
    }
}

void CDraft::drawFont(const int x, const int y, const char *s, uint16_t color) const
{
    // ESP_LOGI(TAG, "Draw Font at (%d,%d): %s", x, y, s);
    uint8_t *font = &bitfont_bin;
    for (int j = 0; s[j]; ++j)
    {
        int u = s[j] < 127 ? std::max(s[j] - ' ', 0) : 0;
        uint16_t *o = m_buf + x + y * m_width + FONT_SIZE * j;
        for (int yy = 0; yy < FONT_SIZE; ++yy)
        {
            uint8_t data = font[FONT_OFFSET * u + yy];
            for (int xx = 0; xx < FONT_SIZE; ++xx)
            {
                o[xx] = data & 1 ? color : 0;
                data = data >> 1;
            }
            o += m_width;
        }
    }
}

void CDraft::drawRect(const Rect &rect, const uint16_t color, const bool fill) const
{
    uint16_t *buf = m_buf + rect.x + rect.y * m_width;
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
