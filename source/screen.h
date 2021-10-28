#pragma once

#include <cstdint>
#include "common.h"

constexpr uint32_t ON_COLOR = 0xFFFFFFFF;
constexpr uint32_t OFF_COLOR = 0x000000FF;

bool GetPixel(int x, int y);
void SetPixel(int x, int y, bool value);
void ClearScreen();
bool DrawByte(int value, int x, int y);

void CreateScreen();
void RenderFrame();
void DeleteScreen();