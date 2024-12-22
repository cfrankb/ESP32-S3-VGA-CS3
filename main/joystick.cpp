#include "joystick.h"

#include "esp_log.h"
#include "esp_idf_version.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"

static const char *TAG = "joystick";

CGameController::CGameController(const gpio_num_t pinUp, const gpio_num_t pinDown, const gpio_num_t pinLeft, const gpio_num_t pinRight)
{
    m_buttonsGPIO[Up] = pinUp;
    m_buttonsGPIO[Down] = pinDown;
    m_buttonsGPIO[Left] = pinLeft;
    m_buttonsGPIO[Right] = pinRight;
    init();
}

CGameController::~CGameController()
{
}

uint16_t CGameController::read()
{
    uint8_t result = 0;
    uint8_t mask = 1;
    for (int i = 0; i < ButtonCount; ++i)
    {
        const gpio_num_t &buttonGPIO = m_buttonsGPIO[i];
        if (buttonGPIO != -1)
        {
            result += gpio_get_level(buttonGPIO) * mask;
        }
        mask *= 2;
    }
    return result;
}

void CGameController::init()
{
    for (int i = 0; i < ButtonCount; ++i)
    {
        const gpio_num_t &buttonGPIO = m_buttonsGPIO[i];
        ESP_LOGI(TAG, "[I] BUTTON_%c GPIO = %d", 'A' + i, buttonGPIO);
        if (buttonGPIO != -1)
        {
            ESP_ERROR_CHECK(gpio_set_direction(buttonGPIO, GPIO_MODE_INPUT));
            ESP_ERROR_CHECK(gpio_set_pull_mode(buttonGPIO, GPIO_PULLUP_PULLDOWN));
        }
    }
}