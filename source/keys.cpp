#include "keys.h"

#include <cassert>
#include <SDL.h>

bool pressed_keys[16];
bool released_keys[16];

bool IsKeyPressed(int value){
    assert(value >=0 && value <= 15);
    return pressed_keys[value];
}

bool IsKeyReleased(int value){
    assert(value >=0 && value <= 15);
    return released_keys[value];
}

void ProcessKeys(){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for(int i = 0; i <= 15; i++){
        bool last = pressed_keys[i];
        bool newOne = state[keys[i]] == 1;
        released_keys[i] = last && !newOne;
        pressed_keys[i] = newOne;
    }
}