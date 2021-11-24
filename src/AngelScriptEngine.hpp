#pragma once
#include "stdafx.h"
#include "BaseScriptEngine.hpp"

class asIScriptEngine;
namespace std {
	template<class T, class D>
	class unique_ptr;
}
namespace BEbraEngine {
	class AngelScriptEngine : public BaseScriptEngine
	{
	public:
		AngelScriptEngine();

		~AngelScriptEngine();

		std::optional<BaseScript*> createScript(std::string path, std::string name);

		void executeScript(BaseScript* script);

		BaseScript* CreateScript(std::string code) override;
	private:

		asIScriptEngine* engine;
	};
}


