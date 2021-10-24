#include <SDL.h>

#include "screen.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

uint32_t* frameBuffer;

void CreateScreen(){
    window = SDL_CreateWindow(APP_TITLE, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * SCREEN_MULTIPLIER, SCREEN_HEIGHT * SCREEN_MULTIPLIER,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    frameBuffer = new uint32_t[SCREEN_WIDTH * SCREEN_HEIGHT];

    for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
        pixels[i] = false;
        frameBuffer[i] = OFF_COLOR;
    }

    SDL_ShowWindow(window);
}

void RenderFrame(){
    for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
        frameBuffer[i] = pixels[i] ? ON_COLOR : OFF_COLOR;
    }

    SDL_UpdateTexture(texture, NULL, frameBuffer, 
        SCREEN_WIDTH * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

void DeleteScreen(){
    delete frameBuffer;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}