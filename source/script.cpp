#include <random>
#include <functional>
#include <ctime>
#include "script.h"
#include "common.h"

#include "lua.hpp"
#include "screen.h"
#include "keys.h"
#include "sound.h"
#include <iostream>

const int font[16][5] = {
    {0xF0, 0x90, 0x90, 0x90, 0xF0}, //0
    {0x20, 0x60, 0x20, 0x20, 0x70}, //1
    {0xF0, 0x10, 0xF0, 0x80, 0xF0}, //2
    {0xF0, 0x10, 0xF0, 0x10, 0xF0}, //3
    {0x90, 0x90, 0xF0, 0x10, 0x10}, //4
    {0xF0, 0x80, 0xF0, 0x10, 0xF0}, //5
    {0xF0, 0x80, 0xF0, 0x90, 0xF0}, //6
    {0xF0, 0x10, 0x20, 0x40, 0x40}, //7
    {0xF0, 0x90, 0xF0, 0x90, 0xF0}, //8
    {0xF0, 0x90, 0xF0, 0x10, 0xF0}, //9
    {0xF0, 0x90, 0xF0, 0x90, 0x90}, //A
    {0xE0, 0x90, 0xE0, 0x90, 0xE0}, //B
    {0xF0, 0x80, 0x80, 0x80, 0xF0}, //C
    {0xE0, 0x90, 0x90, 0x90, 0xE0}, //D
    {0xF0, 0x80, 0xF0, 0x80, 0xF0}, //E
    {0xF0, 0x80, 0xF0, 0x80, 0x80}, //F
    };

lua_State* lua;

int delay_timer;
int sound_timer;

std::default_random_engine generator{static_cast<long unsigned int>(time(0))};

int ErrorHandler(lua_State *L){
    std::cout<<lua_tostring(lua, -1)<<std::endl;
    quit = true;
    return 1;
}

int LuaClearScreen(lua_State *L){
    if(lua_gettop(lua) != 0){
        luaL_error(lua, "expecting no arguments");
    }

    ClearScreen();
    return 0;
}

int LuaDraw(lua_State* L){
    int start, len;
    if(lua_gettop(lua) == 5){
        start = luaL_checkinteger(lua, 4);
        len = luaL_checkinteger(lua, 5);
        luaL_argcheck(lua, (start >= 1), 4, "must be larger than 0");
        luaL_argcheck(lua, (len >= 0 && len <= SCREEN_HEIGHT), 5, "must be between 0 and 31");
    }
    else if(lua_gettop(lua) == 3){
        start = 1;
        len = SCREEN_HEIGHT;
    }
    else{
        luaL_error(lua, "expecting either 3 or 5 arguments");
    }
    
    bool result = false;
    int x = luaL_checkinteger(lua, 2);
    int y = luaL_checkinteger(lua, 3);

    luaL_argcheck(lua, lua_istable(lua, 1), 1, "must be a table");
    luaL_argcheck(lua, (x >= 0 && x < SCREEN_WIDTH), 2, "must be between 0 and 63");
    luaL_argcheck(lua, (y >= 0 && y < SCREEN_HEIGHT), 3, "must be between 0 and 31");

    for(int i = start; i < start + len; i++){
        lua_geti(lua, 1, i);
        if(lua_isnil(lua, -1)){
            lua_pop(lua, 2);
            break;
        }
        int b = luaL_checkinteger(lua, -1);
        if(b < 0 || b > 255)
        {
            luaL_error(lua, "can't draw %d, must be between 0 and 255", b);
        }
        if(!result && DrawByte(b, x, y+i-1)){
            result = true;
        }
        lua_pop(lua, 1);
    }
    lua_pop(lua, 1);
    lua_pushboolean(lua, result);
    return 1;
}

int LuaRnd(lua_State* L){
    if(lua_gettop(lua) != 1){
        luaL_error(lua, "expecting 1 argument");
    }

    int value = luaL_checkinteger(lua, -1);
    lua_pop(lua, 1);

    luaL_argcheck(lua, (value >=0 && value <= 255), 1, "must be between 0 and 255");

    std::uniform_int_distribution<int> distribution(0, value - 1);
    distribution(generator);
    int r = distribution(generator);
    int new_num = r % value;
    //std::cout<<"generated "<<new_num<<std::endl;
    lua_pushinteger(lua, new_num);
    return 1;
}

static void dumpstack (lua_State *L) {
  int top=lua_gettop(L);
  for (int i=1; i <= top; i++) {
    printf("%d\t%s\t", i, luaL_typename(L,i));
    switch (lua_type(L, i)) {
      case LUA_TNUMBER:
        printf("%g\n",lua_tonumber(L,i));
        break;
      case LUA_TSTRING:
        printf("%s\n",lua_tostring(L,i));
        break;
      case LUA_TBOOLEAN:
        printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
        break;
      case LUA_TNIL:
        printf("%s\n", "nil");
        break;
      default:
        printf("%p\n",lua_topointer(L,i));
        break;
    }
  }
}

int LuaKeyPressed(lua_State* L){
    if(lua_gettop(lua) != 1){
        luaL_error(lua, "expecting 1 argument");
    }

    int result = 0;
    int value = luaL_checkinteger(lua, -1);
    luaL_argcheck(lua, (value >= 0 && value <= 15), 1, "must be between 0 and 15");
    lua_pop(lua, 1);
    lua_pushboolean(lua, IsKeyPressed(value));
    return 1;
}

int LuaKeyReleased(lua_State* L){
    if(lua_gettop(lua) != 1){
        luaL_error(lua, "expecting 1 argument");
    }

    int result = 0;
    int value = luaL_checkinteger(lua, -1);
    luaL_argcheck(lua, (value >= 0 && value <= 15), 1, "must be between 0 and 15");
    lua_pop(lua, 1);
    lua_pushboolean(lua, IsKeyReleased(value));
    return 1;
}

int LuaBcd(lua_State* L){
    if(lua_gettop(lua) != 1){
        luaL_error(lua, "expecting 1 argument");
    }

    int value = luaL_checkinteger(lua, -1);
    luaL_argcheck(lua, (value >= 0 && value <= 2555), 1, "must be between 0 and 255");
    lua_pop(lua, 1);
    lua_newtable(lua);
    lua_pushinteger(lua, value / 100);
    lua_seti(lua, -2, 1);
    lua_pushinteger(lua, (value / 10) % 10);
    lua_seti(lua, -2, 2);
    lua_pushinteger(lua, value % 10);
    lua_seti(lua, -2, 3);
    return 1;
}

int LuaGetSprite(lua_State* L){
    if(lua_gettop(lua) != 1){
        luaL_error(lua, "expecting 1 argument");
    }

    int value = luaL_checkinteger(lua, -1);
    luaL_argcheck(lua, (value >= 0 && value <= 15), 1, "must be between 0 and 15");
    lua_pop(lua, 1);
    lua_createtable(lua, 5, 0);
    for(int i = 1; i <= 5; i++){
        lua_pushinteger(lua, font[value][i-1]);
        lua_seti(lua, -2, i);
    }
    return 1;
}

void CreateLua(){
    delay_timer = 0;
    sound_timer = 0;
    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_register(lua, CLS_FUNCTION, LuaClearScreen);
    lua_register(lua, DRAW_FUNCTION, LuaDraw);
    lua_register(lua, RND_FUNCTION, LuaRnd);
    lua_register(lua, KEY_PRESSED_FUNCTION, LuaKeyPressed);
    lua_register(lua, KEY_RELEASED_FUNCTION, LuaKeyReleased);
    lua_register(lua, BCD_FUNCTION, LuaBcd);
    lua_register(lua, GET_SPRITE_FUNCTION, LuaGetSprite);
}

bool LoadFile(char* fileName){
    if(luaL_dofile(lua, fileName) == LUA_OK){
        return true;
    }
    std::cout<<lua_tostring(lua, -1)<<std::endl;
    return false;
}

void CallVBlank(){
    lua_pushcfunction(lua, ErrorHandler);
    lua_getglobal(lua, VBLANK_FUNCTION);
    if(lua_isfunction(lua, -1)){ 
        lua_pcall(lua, 0, 0, -2);
    }
    else {
        std::cout<<"error: no function vblank()"<<std::endl;
        quit = true;
    }  
}

void ProcessDelayTimer(){
    lua_getglobal(lua, DELAY_TIMER_VARIABLE);
    delay_timer = lua_tointeger(lua, -1);
    lua_pop(lua, 1);

    if(delay_timer > 0){
        delay_timer--;
    }
    else if (delay_timer < 0){
        delay_timer++;
    }
   // std::cout<<"delay_timer "<<delay_timer<<std::endl;
    lua_pushinteger(lua, delay_timer);
    lua_setglobal(lua, DELAY_TIMER_VARIABLE);
}

void ProcessSoundTimer(){
    lua_getglobal(lua, SOUND_TIMER_VARIABLE);
    sound_timer = lua_tointeger(lua, -1);
    lua_pop(lua, 1);

    if(sound_timer > 0){
        sound_timer--;
    }
    else if (sound_timer < 0){
        sound_timer++;
    }

    if(sound_timer != 0){
        if(paused){
            UnpauseSound(); 
        }    
    }
    else{
        if(!paused){
            PauseSound();
        } 
    }
  // std::cout<<"sound_timer "<<sound_timer<<" paused "<<paused<<std::endl;
    lua_pushinteger(lua, sound_timer);
    lua_setglobal(lua, SOUND_TIMER_VARIABLE);
}

void DeleteLua(){
    lua_close(lua);
}