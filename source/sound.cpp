#include <SDL.h>
#include <iostream>

#include "sound.h"
#include "common.h"

SDL_AudioDeviceID dev;

bool paused;
short *buffer;
int current = 0;

void callback(void*  userdata, Uint8* stream, int len){
    short* stream2 = (short*) stream;

    int period = AUDIO_FREQUENCY / SQUARE_WAVE_FREQUENCY;
    for(int i = 0; i < len / sizeof(short); i+=2){
        stream2[i] = ((current++ % period) < (period / 2))
            ? AUDIO_VOLUME : 0;

        stream2[i + 1] = stream2[i];
   }

}

void CreateSound(){
    SDL_AudioSpec want, have;
    SDL_zero(want);
    want.freq = AUDIO_FREQUENCY;
    want.format = AUDIO_S16;
    want.channels = AUDIO_CHANNELS;
    want.samples = AUDIO_BUFFER;
    want.callback = callback;
    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
   // QueueSound();
    paused = true;
}

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
    paused = true;
}

void UnpauseSound(){
    SDL_PauseAudioDevice(dev, 0);
    paused = false;
}

void DeleteSound(){ 
    SDL_PauseAudioDevice(dev, 1);
    SDL_CloseAudioDevice(dev);
}