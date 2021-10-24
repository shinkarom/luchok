#include <iostream>
#include <chrono>
#include <thread>

#include <lua.hpp>
#include <SDL.h>

#include "screen.h"
#include "script.h"

int main(int argc, char** argv){
    bool quit = false;
    SDL_Event event;

    std::cout << "Luchok\n";
    CreateLua();
    CreateScreen();

    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();    
    while(!quit){  
        next_frame += std::chrono::milliseconds(FRAME_DURATION);
        RenderFrame();
        do{
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }  while ((!quit) && (clock::now() < next_frame));   
    }  

    DeleteScreen();
    DeleteLua();
    return 0;
}