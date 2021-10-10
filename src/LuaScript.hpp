#pragma once
/*
#include "AbstractComponent.hpp"
#include "BaseScript.hpp"
#include <LuaBridge/LuaBridge.h>
namespace BEbraEngine {
	using namespace luabridge;
	class LuaScript : public BaseScript
	{
	private:
		lua_State* script;
	public:
		LuaScript(lua_State* state) : script(state) {}

		void Initialization() override {
			LuaRef func = getGlobal(script, "Init");
			if (func.isFunction()) {
				func();
			}
			else {
				throw std::exception("failed to execute the script");
			}
		}

		void Run() override {
			LuaRef func = getGlobal(script, "Tick");
			if (func.isFunction()) {
				func();
			}
			else {
				throw std::exception("failed to execute the script");
			}
		}

		void Destroy() override {

		}
	};
}
*/
