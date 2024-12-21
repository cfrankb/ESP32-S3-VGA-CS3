#include <stdio.h>

#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "soc/gpio_struct.h"
#include "soc/gpio_reg.h"
#include <rom/ets_sys.h>

#include "pins.h"
#include "VGA.h"

void delayMS(int ms)
{
    int _ms = ms + (portTICK_PERIOD_MS - 1);
    TickType_t xTicksToDelay = _ms / portTICK_PERIOD_MS;
    // ESP_LOGD(TAG, "ms=%d _ms=%d portTICK_PERIOD_MS=%d xTicksToDelay=%d", ms, _ms, portTICK_PERIOD_MS, xTicksToDelay);
    vTaskDelay(xTicksToDelay);
}

void vga_3bits_test()
{
    const int WIDTH = 320;
    const int HEIGHT = 240;
    VGA vga;
    // vga.init(320, 240, 2, 0, 0, 1, nullptr, false);
    vga.initWithSize(WIDTH, HEIGHT, 3);
    uint8_t v = 0;
    while (1)
    {
        uint8_t vv = v + (v << 4);
        vga.vsyncWait();
        auto buf = vga.getDrawBuffer();
        int count = (WIDTH / 2) * HEIGHT;
        for (int i = 0; i < count; ++i)
        {
            buf[i] = vv;
        }
        delayMS(500);
        ++v;
        v &= 7;
    }
}

void vga_8bits_test()
{
    const int WIDTH = 320;
    const int HEIGHT = 240;
    VGA vga;
    // vga.init(320, 240, 2, 0, 0, 1, nullptr, false);
    vga.initWithSize(WIDTH, HEIGHT, 8);
    uint8_t v = 0;
    while (1)
    {
        vga.vsyncWait();
        auto buf = vga.getDrawBuffer();
        int count = WIDTH * HEIGHT;
        for (int i = 0; i < count; ++i)
        {
            buf[i] = v;
        }
        delayMS(500);
        ++v;
        // v &= 7;
    }
}

extern "C" void app_main(void)
{
    //  vga_3bits_test();
    vga_8bits_test();
}
