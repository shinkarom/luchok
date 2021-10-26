#include <cstdlib>
#include <ctime>
#include "script.h"
#include "common.h"

#include "lua.hpp"
#include "screen.h"
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

int LuaClearScreen(lua_State *L){
    ClearScreen();
    return 0;
}

int LuaDraw(lua_State* L){
    bool result = false;
    int count = luaL_checkinteger(lua, -1);
    int y = luaL_checkinteger(lua, -2);
    int x = luaL_checkinteger(lua, -3);
    lua_pop(lua, 3);
    for(int i = 1; i <= count; i++){
        lua_geti(lua, -1, i);
        int b = luaL_checkinteger(lua, -1);
        if(!result && DrawByte(b, x, y+i-1)){
            result = true;
        }
        lua_pop(lua, 1);
    }
    lua_pop(lua, 1);
    lua_pushinteger(lua, result ? 1 : 0);
    return 1;
}

int LuaDrawFont(lua_State* L){
    bool result = false;
    int y = luaL_checkinteger(lua, -1);
    int x = luaL_checkinteger(lua, -2);
    int index = luaL_checkinteger(lua, -3);

    for(int i = 0; i < 5; i++){
        if(!result && DrawByte(font[index][i], x, y + i)){
            result = true;
        }
    }

    lua_pop(lua, 3);
    lua_pushinteger(lua, result ? 1 : 0);
    return 1;
}

int LuaRnd(lua_State* L){
    int value = luaL_checkinteger(lua, -1);
    lua_pop(lua, 1);

    int r = rand() % 256;
    int new_num = r & value;

    lua_pushinteger(lua, new_num);
    return 1;
}

void CreateLua(){
    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_pushcfunction(lua, LuaClearScreen);
    lua_setglobal(lua, CLS_FUNCTION);
    lua_pushcfunction(lua, LuaDraw);
    lua_setglobal(lua, DRAW_FUNCTION);
    lua_pushcfunction(lua, LuaDrawFont);
    lua_setglobal(lua, DRAW_FONT_FUNCTION);
    lua_pushcfunction(lua, LuaRnd);
    lua_setglobal(lua, RND_FUNCTION);
}

bool LoadFile(char* fileName){
    if(luaL_dofile(lua, fileName) == LUA_OK){
        return true;
    }
    return false;
}

void RunLua(){
    if(lua_pcall(lua, 0, LUA_MULTRET, 0) == LUA_OK){
        lua_pop(lua, lua_gettop(lua));
    }
}

void CallVBlank(){
    lua_getglobal(lua, VBLANK_FUNCTION);
    if(lua_isfunction(lua, -1)){
        lua_pcall(lua, 0, LUA_MULTRET, 0);
    }
}

void ProcessDelayTimer(){
    lua_getglobal(lua, DELAY_TIMER_VARIABLE);
    delay_timer = lua_tointeger(lua, -1);
    lua_pop(lua, -1);

    if(delay_timer > 0){
        delay_timer--;
    }
    else if (delay_timer < 0){
        delay_timer++;
    }

    lua_pushinteger(lua, delay_timer);
    lua_setglobal(lua, DELAY_TIMER_VARIABLE);
}

void DeleteLua(){
    lua_close(lua);
}