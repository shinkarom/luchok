#pragma once
#include "common.h"

constexpr int AUDIO_FREQUENCY = 48000;
constexpr int AUDIO_BUFFER = 2048;
constexpr int AUDIO_CHANNELS = 2;
constexpr int AUDIO_STREAM_LENGTH = AUDIO_FREQUENCY / FRAMERATE;
constexpr int SQUARE_WAVE_FREQUENCY = 440;
constexpr short AUDIO_VOLUME = 28000;

void CreateSound();
void QueueSound();
void PauseSound();
void UnpauseSound();
void DeleteSound();

extern bool paused;