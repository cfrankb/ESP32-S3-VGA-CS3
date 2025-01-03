
#include <esp_log.h>
#include <cstring>
#include <string>
#include <stdint.h>
#include "engine.h"
#include "game.h"
#include "colors.h"
#include "draft.h"
#include "tilesdata.h"
#include "joystick.h"
#include "animzdata.h"
#include "maparch.h"
#include "animator.h"
#include "conf.h"
#include "data.h"
#include "VGA.h"

static const char *TAG = "engine";
static CDraft draft(CONFIG_WIDTH, CEngine::TILE_SIZE);

std::mutex g_mutex;
CEngine *g_engine = nullptr;
CEngine *CEngine::getEngine()
{
    if (!g_engine)
    {
        g_engine = new CEngine();
    }
    return g_engine;
}

CEngine::CEngine()
{
    if (!init())
    {
        printf("loading mapIndex failed\n");
    }
}

CEngine::~CEngine()
{
    if (m_game)
    {
        delete m_game;
    }
}

CGame &CEngine::game()
{
    return *m_game;
}

void CEngine::drawLevelIntro(VGA *vga)
{
    ESP_LOGI(TAG, "Draw Level Intro");

    char t[32];
    switch (m_game->mode())
    {
    case CGame::MODE_INTRO:
        sprintf(t, "LEVEL %.2d", m_game->level() + 1);
        break;
    case CGame::MODE_RESTART:
        if (m_game->lives() == 1)
        {
            strcpy(t, "ONE LIFE LEFT");
            break;
        }
        sprintf(t, "LIVES LEFT %.2d", m_game->lives());
        break;
    case CGame::MODE_GAMEOVER:
        strcpy(t, "GAME OVER");
    };

    int x = (CONFIG_WIDTH - strlen(t) * FONT_SIZE) / 2;
    int y = (CONFIG_HEIGHT - FONT_SIZE) / 2;
    vga->clear(BLACK);
    draft.fill(BLACK);
    draft.drawFont(x, 0, t, WHITE);
    vga->drawBuffer(0, y, draft.buf(), draft.width(), FONT_SIZE);
}

void CEngine::drawKeys(const CDraft &display, const int y)
{
    CGame &game = *m_game;
    int x = CONFIG_WIDTH - TILE_SIZE;
    const uint8_t *keys = game.keys();
    for (int i = 0; i < CGame::MAX_KEYS; ++i)
    {
        uint8_t k = keys[i];
        if (k)
        {
            display.drawTile(x, y, reinterpret_cast<uint16_t *>(&tiles_mcz) + k * TILE_OFFSET, true);
            x -= TILE_SIZE;
        }
    }
}

void CEngine::drawScreen(VGA *vga)
{
    // ESP_LOGI(TAG, "Starting drawscreen");
    std::lock_guard<std::mutex> lk(g_mutex);
    CMap &map = m_game->getMap();
    CActor &player = m_game->player();

    const int cols = CONFIG_WIDTH / TILE_SIZE;
    const int rows = CONFIG_HEIGHT / TILE_SIZE;
    const int lmx = std::max(0, player.getX() - cols / 2);
    const int lmy = std::max(0, player.getY() - rows / 2);
    const int mx = std::min(lmx, map.len() > cols ? map.len() - cols : 0);
    const int my = std::min(lmy, map.hei() > rows ? map.hei() - rows : 0);

    CActor *monsters;
    int count;
    m_game->getMonsters(monsters, count);

    uint16_t *tiledata;
    for (int y = 0; y < rows; ++y)
    {
        if (y == rows - 1)
        {
            // draw bottom rect
            draft.drawRect(
                Rect{.x = 0, .y = 0, .width = CONFIG_WIDTH, .height = TILE_SIZE}, GRAY, true);
            draft.drawRect(
                Rect{.x = 0, .y = 0, .width = CONFIG_WIDTH, .height = TILE_SIZE}, LIGHTGRAY, false);

            // draw health bar
            draft.drawRect(
                Rect{.x = 4, .y = 4, .width = std::min(m_game->health() / 2, CONFIG_WIDTH - 4), .height = TILE_SIZE / 2}, LIME, true);
            draft.drawRect(
                Rect{.x = 4, .y = 4, .width = std::min(m_game->health() / 2, CONFIG_WIDTH - 4), .height = TILE_SIZE / 2}, WHITE, false);

            drawKeys(draft, 0 * TILE_SIZE);
            vga->drawBuffer(0, y * TILE_SIZE, draft.buf(), draft.width(), draft.height());
            continue;
        }

        for (int x = 0; x < cols; ++x)
        {
            int j;
            int i = y + my >= map.hei() ? TILES_BLANK : map.at(x + mx, y + my);
            if (i == TILES_ANNIE2)
            {
                const int frame = player.getAim() * PLAYER_FRAMES + m_playerFrameOffset;
                tiledata = reinterpret_cast<uint16_t *>(&annie_mcz) + TILE_OFFSET * frame;
            }
            else
            {
                if (i == TILES_STOP)
                {
                    i = TILES_BLANK;
                }
                j = m_animator->at(i);
                tiledata = (j == NO_ANIMZ)
                               ? reinterpret_cast<uint16_t *>(&tiles_mcz) + i * TILE_OFFSET
                               : reinterpret_cast<uint16_t *>(&animz_mcz) + j * TILE_OFFSET;
            }
            if (y == 0)
            {
                draft.drawTile32(x * TILE_SIZE, 0, tiledata);
            }
            else
            {
                vga->drawTile(x * TILE_SIZE, y * TILE_SIZE, tiledata);
            }
        }

        const int offset = m_animator->offset() & 7;
        for (int i = 0; i < count; ++i)
        {
            const CActor &monster = monsters[i];
            if (monster.within(mx, my + y, mx + cols, my + y + 1))
            {
                const uint8_t tileID = map.at(monster.getX(), monster.getY());
                if (!m_animator->isSpecialCase(tileID))
                {
                    continue;
                }
                // special case animations
                const int xx = monster.getX() - mx;
                tiledata = reinterpret_cast<uint16_t *>(&animz_mcz) + (monster.getAim() * 8 + ANIMZ_INSECT1 + offset) * TILE_OFFSET;
                if (y == 0)
                {
                    draft.drawTile32(xx * TILE_SIZE, 0, tiledata);
                }
                else
                {
                    vga->drawTile(xx * TILE_SIZE, y * TILE_SIZE, tiledata);
                }
            }
        }

        if (y == 0)
        {
            char tmp[32];
            int bx = 0;
            int offsetY = 0;
            sprintf(tmp, "%.8d ", m_game->score());
            draft.drawFont(0, offsetY, tmp, WHITE);

            bx += strlen(tmp);
            sprintf(tmp, "DIAMONDS %.2d ", m_game->diamonds());
            draft.drawFont(bx * FONT_SIZE, offsetY, tmp, YELLOW);

            bx += strlen(tmp);
            sprintf(tmp, "LIVES %.2d ", m_game->lives());
            draft.drawFont(bx * FONT_SIZE, offsetY, tmp, PURPLE);

            vga->drawBuffer(0, 0, draft.buf(), draft.width(), draft.height());
        }
    }
}

bool CEngine::init()
{
    m_game = new CGame();
    m_animator = new CAnimator();
    return m_game->loadMapIndex();
}

std::mutex &CEngine::mutex()
{
    return g_mutex;
}

void CEngine::mainLoop(const int ticks)
{
    CGame &game = *m_game;
    if (game.mode() != CGame::MODE_LEVEL)
    {
        return;
    }

    const uint16_t joyState = m_gamepad ? m_gamepad->read() : 0; // readJoystick();
    if (ticks % PLAYER_SPEED == 0 && !game.isPlayerDead())
    {
        game.managePlayer(joyState);
    }

    if (ticks % PLAYER_SPEED == 0)
    {
        // ESP_LOGI(TAG, "joyState 0x%.4x", joyState);
        if (game.health() < m_healthRef && m_playerFrameOffset != PLAYER_REG_FRAMES)
        {
            m_playerFrameOffset = PLAYER_REG_FRAMES;
        }
        else if (joyState)
        {
            m_playerFrameOffset = (m_playerFrameOffset + 1) % PLAYER_REG_FRAMES;
        }
        else
        {
            m_playerFrameOffset = 0;
        }
        m_healthRef = game.health();
        m_animator->animate();
    }

    game.manageMonsters(ticks);

    if (!game.isGameOver())
    {
        if (game.goalCount() == 0)
        {
            m_healthRef = 0;
            mutex().lock();
            game.nextLevel();
            mutex().unlock();
        }
    }
}

void CEngine::attach(IJoystick *gamepad)
{
    m_gamepad = gamepad;
}