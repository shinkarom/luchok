#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#include <SDL.h>

#include "screen.h"
#include "script.h"
#include "keys.h"
#include "sound.h"
bool quit;

void ProcessFrames(){
    quit = false;
    SDL_Event event;
    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();   
    while(!quit){ 
        next_frame += std::chrono::milliseconds(FRAME_DURATION);   
        ClearScreen();
        ProcessDelayTimer();
        //QueueSound();
        ProcessSoundTimer();
        ProcessKeys();
        CallVBlank();  
        RenderFrame();
        do{
            SDL_WaitEventTimeout(&event, 2);
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }  while ((!quit) && (clock::now() < next_frame)); 
        //std::cout<<"-----"<<std::endl;  
    } 
}

int main(int argc, char** argv){
    std::cout << "Luchok\n";

    srand(time(0));

    SDL_Init(SDL_INIT_AUDIO);

    CreateLua();
    CreateScreen();
    CreateSound();

    if(argc > 1){
        if(LoadFile(argv[1])){
            std::cout << argv[1] << " loaded successfully." << std::endl;
            ProcessFrames();
        }
        else{
            std::cout << "Couldn't load " << argv[1] << "." << std::endl;
        }
    }
    else{
        std::cout << "No file provided." << std::endl;
    }

    DeleteSound();
    DeleteScreen();
    DeleteLua();

    SDL_Quit();

    return 0;
}