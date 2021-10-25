#pragma once

#include "common.h"

constexpr int FRAME_DURATION = 1000 / 60;
constexpr uint32_t ON_COLOR = 0xFFFFFFFF;
constexpr uint32_t OFF_COLOR = 0x000000FF;

bool GetPixel(int x, int y);
void SetPixel(int x, int y, bool value);

void CreateScreen();
void RenderFrame();
void DeleteScreen();