#pragma once
#include "BaseScriptEngine.hpp"
#include "BaseScript.hpp"
class lua_State;
namespace BEbraEngine {

    class LuaEngine : public IScriptFactory
    {
    private:
        void CreateGlobalContext(lua_State* L);
    public:
        BaseScript* CreateScript(std::string code) override;
    };
}
