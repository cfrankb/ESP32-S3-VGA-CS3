#pragma once

#include <stdint.h>
#include "driver/gpio.h"

enum JoyDir
{
    JOY_UP = 0x01,
    JOY_DOWN = 0x02,
    JOY_LEFT = 0x04,
    JOY_RIGHT = 0x08,
    JOY_BUTTON = 0x10,
    JOY_A_BUTTON = 0x20,
    JOY_NONE = 0
};

#define NO_PIN static_cast<gpio_num_t>(-1)

class IJoystick
{
protected:
    IJoystick() {};
    virtual ~IJoystick() {};
    enum
    {
        Up,
        Down,
        Left,
        Right,
        ButtonCount = 4
    };

public:
    virtual uint16_t read() = 0;
};

class CGameController : public IJoystick
{
public:
    CGameController(const gpio_num_t pinUp, const gpio_num_t pinDown, const gpio_num_t pinLeft, const gpio_num_t pinRight);
    ~CGameController() override;

    uint16_t read() override;

private:
    void init();
    gpio_num_t m_buttonsGPIO[ButtonCount];
};
