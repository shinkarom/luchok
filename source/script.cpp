#include "script.h"
#include "common.h"

#include "lua.hpp"
#include "screen.h"
#include <iostream>

lua_State* lua;

int LuaClearScreen(lua_State *L){
    ClearScreen();
    return 0;
}

void CreateLua(){
    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_pushcfunction(lua, LuaClearScreen);
    lua_setglobal(lua, CLs_FUNCTION);
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

void DeleteLua(){
    lua_close(lua);
}