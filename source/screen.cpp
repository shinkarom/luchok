#include <SDL.h>

#include "screen.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

bool pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
uint32_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

void CreateScreen(){
    window = SDL_CreateWindow(APP_TITLE, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * SCREEN_MULTIPLIER, SCREEN_HEIGHT * SCREEN_MULTIPLIER,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
        pixels[i] = false;
    }

    SDL_ShowWindow(window);
}

bool GetPixel(int x, int y){
    return frameBuffer[y * SCREEN_WIDTH + x] == ON_COLOR;
}

void SetPixel(int x, int y, bool value){
    frameBuffer[y * SCREEN_WIDTH + x] = value ? ON_COLOR : OFF_COLOR;
}

void RenderFrame(){
    SDL_UpdateTexture(texture, NULL, frameBuffer, 
        SCREEN_WIDTH * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void DeleteScreen(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}