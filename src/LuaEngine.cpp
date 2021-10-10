
/*
extern "C" {

#pragma comment(lib, "legacy_stdio_definitions")

#include <stdio.h>
    FILE _iob[] = { *stdin, *stdout, *stderr };
    extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "LuaEngine.hpp"
#include <LuaBridge/LuaBridge.h>

#include "LuaScript.hpp"




using namespace luabridge;
#include <iostream>

inline void printMessage(const std::string& s) {
    printf(s.c_str());
}
namespace BEbraEngine {
    void LuaEngine::CreateGlobalContext(lua_State* L)
    {
        getGlobalNamespace(L)
            .addFunction("print", printMessage);
    }

    BaseScript* LuaEngine::CreateScript(std::string code)
    {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        CreateGlobalContext(L);
        if (luaL_loadstring(L, code.c_str()) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
            throw std::exception("failed to load script");
        }
        return new LuaScript(L);

    }
}
*/