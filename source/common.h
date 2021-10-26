#pragma once

constexpr int SCREEN_WIDTH = 64;
constexpr int SCREEN_HEIGHT = 32;
constexpr int SCREEN_MULTIPLIER = 10;
constexpr int FRAMERATE = 60;
static const char* APP_TITLE = "Luchok";
static const char* VBLANK_FUNCTION = "vblank";
static const char* CLS_FUNCTION = "cls";
static const char* DRAW_FUNCTION = "draw";
static const char* DRAW_FONT_FUNCTION = "draw_font";
static const char* RND_FUNCTION = "rnd";
static const char* DELAY_TIMER_VARIABLE = "delay_timer";

static int delay_timer = 0;