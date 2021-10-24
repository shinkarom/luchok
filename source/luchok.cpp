#include <iostream>
#include <lua.hpp>
#include <SDL.h>

#include "screen.h"

int main(int argc, char** argv){
    std::cout << "Luchok\n";
    CreateScreen();
    RenderFrame();
    DeleteScreen();
    return 0;
}