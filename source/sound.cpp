#include <SDL.h>
#include <iostream>

#include "sound.h"
#include "common.h"

SDL_AudioDeviceID dev;


void CreateSound(){
    SDL_AudioSpec want, have;
    SDL_zero(want);
    want.freq = AUDIO_FREQUENCY;
    want.format = AUDIO_S16;
    want.channels = AUDIO_CHANNELS;
    want.samples = AUDIO_BUFFER;
    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    QueueSound();
}

int current = 0;

void QueueSound(){ 
    short *buffer = new short[AUDIO_STREAM_LENGTH * AUDIO_CHANNELS];
    int period = AUDIO_FREQUENCY / SQUARE_WAVE_FREQUENCY;

    for(int i = 0; i < AUDIO_STREAM_LENGTH; i++){
        buffer[i * AUDIO_CHANNELS] = ((i % period) < (period / 2))
            ? AUDIO_VOLUME : 0;

        buffer[i * AUDIO_CHANNELS + 1] = buffer[i * AUDIO_CHANNELS];
   }

   SDL_QueueAudio(dev, buffer, AUDIO_STREAM_LENGTH * AUDIO_CHANNELS); 
   delete[] buffer;
}

void PauseSound(){
    SDL_PauseAudioDevice(dev, 1);
}

void UnpauseSound(){
    SDL_PauseAudioDevice(dev, 0);
}

void DeleteSound(){ 
    SDL_PauseAudioDevice(dev, 1);
    SDL_CloseAudioDevice(dev);
}