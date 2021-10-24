#include <iostream>
#include <lua.hpp>
#include <SDL.h>

#include "screen.h"
#include "script.h"

int main(int argc, char** argv){
    std::cout << "Luchok\n";
    CreateLua();
    CreateScreen();
    RenderFrame();
    DeleteScreen();
    DeleteLua();
    return 0;
}