#include <iostream>
#include "LedCube.h"
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>

int lua_setLedCubeState(lua_State *L);
LedCubeState luaTableToLedCubeState(lua_State *L);

bool CheckLua(lua_State *L, int r)
{
    if(r != LUA_OK){
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    system("clear");
    LedCube lc;
    int status;
    lua_State *L;

    lc = LedCube();
    L = luaL_newstate();

    // lc.setState(lc.getState());

    luaL_openlibs(L);
    lua_register(L, "__internal__setLedCubeState", lua_setLedCubeState);
    CheckLua(L, luaL_dofile(L, "auto.lua"));

    return 0;
}

int lua_setLedCubeState(lua_State *L)
{

    LedCube lc;

    lc = LedCube();
    lc.setState(luaTableToLedCubeState(L));
    //

    return 0;
}

LedCubeState luaTableToLedCubeState(lua_State *L)
{
    LedCubeState lcs;
    for (int i = 1; i <= 3; i++)
    {
        lua_pushinteger(L, i);
        lua_gettable(L, -2);

        for (int j = 1; j <= 3; j++)
        {
            lua_pushinteger(L, j);
            lua_gettable(L, -2);

            for (int k = 1; k <= 3; k++)
            {

                lua_pushinteger(L, k);
                lua_gettable(L, -2);

                lcs.layers[i - 1].leds[j - 1][k - 1].value = lua_tointeger(L, -1);

                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }
    return lcs;
}