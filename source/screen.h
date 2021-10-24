#pragma once

#include <SDL.h>

#include "common.h"

static bool pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

void CreateScreen();
void RenderFrame();
void DeleteScreen();