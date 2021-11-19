#pragma once
#include "BaseScriptEngine.hpp"
namespace BEbraEngine {
	class AngelScriptEngine : public BaseScriptEngine
	{
	public:
		AngelScriptEngine();
		// Унаследовано через BaseScriptEngine
		virtual BaseScript* CreateScript(std::string code) override;
	};
}


