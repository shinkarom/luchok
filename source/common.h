#pragma once

constexpr int SCREEN_WIDTH = 64;
constexpr int SCREEN_HEIGHT = 32;
constexpr int SCREEN_MULTIPLIER = 10;
constexpr int FRAMERATE = 60;
constexpr int FRAME_DURATION = 1000 / FRAMERATE;
static const char* APP_TITLE = "Luchok";
static const char* VBLANK_FUNCTION = "vblank";
static const char* CLS_FUNCTION = "cls";
static const char* DRAW_FUNCTION = "draw";
static const char* RND_FUNCTION = "rnd";
static const char* KEY_PRESSED_FUNCTION = "key_pressed";
static const char* KEY_RELEASED_FUNCTION = "key_released";
static const char* BCD_FUNCTION = "bcd";
static const char* GET_SPRITE_FUNCTION = "get_sprite";
static const char* DELAY_TIMER_VARIABLE = "delay_timer";
static const char* SOUND_TIMER_VARIABLE = "sound_timer";

extern int delay_timer;
extern int sound_timer;
extern bool quit;