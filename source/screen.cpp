#include <SDL.h>
#include <iostream>

#include "screen.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

uint32_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

void CreateScreen(){
    window = SDL_CreateWindow(APP_TITLE, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * SCREEN_MULTIPLIER, SCREEN_HEIGHT * SCREEN_MULTIPLIER,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_ShowWindow(window);
}

bool GetPixel(int x, int y){
    return frameBuffer[y * SCREEN_WIDTH + x] == ON_COLOR;
}

void SetPixel(int x, int y, bool value){
    frameBuffer[y * SCREEN_WIDTH + x] = value ? ON_COLOR : OFF_COLOR;
}

bool DrawByte(int value, int x, int y){
    bool result = false;
    for(int i = 0; i < 8; i++){
        bool thisBit = (value >> (7 - i)) & 1;
        auto thisColor = thisBit ? ON_COLOR : OFF_COLOR;

        int new_x = (x + i) % SCREEN_WIDTH;
        if(new_x < 0){
            new_x = SCREEN_WIDTH + new_x;
        }

        int new_y = y % SCREEN_HEIGHT;
        if(new_y < 0){
            new_y = SCREEN_HEIGHT + new_y;
        }

        //std::cout<<x<<" "<<y<<" "<<new_x<<" "<<new_y<<" "<<std::endl;

        bool currentBit = GetPixel(new_x, new_y);
        if(!result && currentBit && thisBit)
        {
            result = true;
        }

        bool newBit = currentBit ^ thisBit;
        SetPixel(new_x, new_y, newBit);
        //std::cout << x<< " " << y << " " 
        //    << currentBit << " " << thisBit << " " << 
        //    newBit << " " << result << std::endl;
    }
    return result;
}

void ClearScreen(){
    for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
        frameBuffer[i] = OFF_COLOR;
    }
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