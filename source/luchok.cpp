#include <iostream>
#include <chrono>
#include <thread>

#include <SDL.h>

#include "screen.h"
#include "script.h"

void ProcessFrames(){
    bool quit = false;
    SDL_Event event;
    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();   

    while(!quit){ 
        next_frame += std::chrono::milliseconds(FRAME_DURATION); 
        //SetPixel(10, 10, !GetPixel(10, 10)); 
        ProcessDelayTimer();
        CallVBlank();    
        RenderFrame();
        do{
            SDL_WaitEventTimeout(&event, 2);
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }  while ((!quit) && (clock::now() < next_frame));   
    } 
}

int main(int argc, char** argv){
    std::cout << "Luchok\n";
    CreateLua();
    CreateScreen();

    if(argc > 1){
        if(LoadFile(argv[1])){
            std::cout << argv[1] << " loaded successfully." << std::endl;
            RunLua();
            ProcessFrames();
        }
        else{
            std::cout << "Couldn't load " << argv[1] << "." << std::endl;
        }
    }
    else{
        std::cout << "No file provided." << std::endl;
    }

    DeleteScreen();
    DeleteLua();
   
    return 0;
}