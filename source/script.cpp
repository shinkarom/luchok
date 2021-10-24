#include "script.h"

#include "lua.hpp"

lua_State* lua;

void CreateLua(){
    lua = luaL_newstate();
}

void DeleteLua(){
    lua_close(lua);
}