#include "script.h"

#include "lua.hpp"

lua_State* lua;

void CreateLua(){
    lua = luaL_newstate();
    luaL_openlibs(lua);
}

bool LoadFile(char* fileName){
    if(luaL_loadfile(lua, fileName) == LUA_OK){
        return true;
    }
    return false;
}

void DeleteLua(){
    lua_close(lua);
}