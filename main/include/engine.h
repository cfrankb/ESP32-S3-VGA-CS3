#pragma once

#include <mutex>

class CGame;
class CAnimator;
class CDraft;

class VGA;

class CEngine
{
public:
    static CEngine *getEngine();
    ~CEngine();

    std::mutex &mutex();
    CGame &game();
    void drawScreen(VGA *vga);
    void drawLevelIntro(VGA *vga);
    void mainLoop(int ticks);

    enum
    {
        FONT_SIZE = 8,
        TILE_SIZE = 16,
        PLAYER_FRAMES = 8,
        NO_ANIMZ = 255,
        TILE_OFFSET = TILE_SIZE * TILE_SIZE,
    };

protected:
    CEngine();
    CAnimator *m_animator = nullptr;
    int m_playerFrameOffset = 0;
    int m_healthRef = 0;
    CGame *m_game = nullptr;
    bool init();
    void drawKeys(const CDraft &display, const int y);
};
