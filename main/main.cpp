// https://embeddedtutorials.com/eps32/esp-idf-cpp-with-cmake-for-esp32/

#include <esp_log.h>
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
// #include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "tileset.h"
#include "display.h"
// #include "joystick.h"
#include "map.h"
#include "level.h"
#include "tilesdata.h"
#include "game.h"
#include "engine.h"
#include "conf.h"
#include "VGA.h"
#include <FONT_8x8.h>

static const char *TAG = "main";
CEngine *engine = nullptr;
VGA vga;

void delayMS(int ms)
{
    int _ms = ms + (portTICK_PERIOD_MS - 1);
    TickType_t xTicksToDelay = _ms / portTICK_PERIOD_MS;
    vTaskDelay(xTicksToDelay);
}

void drawScreenTask(void *pvParameter)
{
    CGame &game = engine->game();
    while (1)
    {
        // ESP_LOGI(TAG, "Waiting on VSync");
        //        vga.vsyncWait();
        //      auto buf = vga.getDrawBuffer();
        switch (game.mode())
        {
        case CGame::MODE_INTRO:
        case CGame::MODE_RESTART:
        case CGame::MODE_GAMEOVER:
            vga.clear(0);
            // engine->drawLevelIntro(buf);
            //         vga.vsyncWait();
            //  buf = vga.getDrawBuffer();
            // engine->drawLevelIntro(buf);
            delayMS(1000);
            if (game.mode() == CGame::MODE_GAMEOVER)
            {
                game.restartGame();
            }
            else
            {
                game.setMode(CGame::MODE_LEVEL);
            }
            break;
        case CGame::MODE_LEVEL:
            engine->drawScreen(&vga);
        }
        delayMS(20);
    }
}

extern "C" void app_main(void)
{

    const PinConfig pins(-1, -1, 6, 7, 8, -1, -1, -1, 12, 13, 14, -1, -1, -1, 18, 21, 1, 2); // R G B h v

    //	Mode mode = Mode::MODE_640x480x60;
    Mode mode = Mode::MODE_320x240x60;

    // if (!vga.init(pins, mode, 16, 3))
    if (!vga.init(pins, mode, 16, 4))
        while (1)
            delayMS(1);

    if (!vga.start())
    {
        ESP_LOGE(TAG, "vga start failed");
    }
    vga.setFont(FONT_8x8);

    // vga_8bits_test();
    delayMS(10);
    ESP_LOGI(TAG, "Initializing VGA driver");
    // vga.initWithSize(CONFIG_WIDTH, CONFIG_HEIGHT, 8);

    ESP_LOGI(TAG, "Free bytes: %ld", esp_get_free_heap_size());

    engine = CEngine::getEngine();
    CGame &game = engine->game();
    ESP_LOGI(TAG, "Free bytes: %ld", esp_get_free_heap_size());

    TaskHandle_t xHandle = NULL;
    BaseType_t xReturned = xTaskCreate(&drawScreenTask, "drawScreen", 4096, NULL, 5, &xHandle);
    ESP_LOGI(TAG, "xReturned:%d", xReturned);

    engine->mutex().lock();
    game.loadLevel(false);
    delayMS(500);
    engine->mutex().unlock();
    // vga_8bits_test(vga);

    ESP_LOGI(TAG, "Free bytes: %ld", esp_get_free_heap_size());

    int ticks = 0;

    ESP_LOGI(TAG, "Starting main loop");
    while (1)
    {
        delayMS(40);

        engine->mainLoop(ticks);
        if (game.isPlayerDead())
        {
            game.killPlayer();
            delayMS(500);
            if (!game.isGameOver())
            {
                engine->mutex().lock();
                game.restartLevel();
                engine->mutex().unlock();
            }
            else
            {
                game.setMode(CGame::MODE_GAMEOVER);
            }
        }

        ++ticks;
    }
}