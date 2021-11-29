#pragma once
#include "stdafx.h"
#include "BaseScriptEngine.hpp"
#include "AngelScript.hpp"
#include "IProxyGameObjectFactory.hpp"
class asIScriptEngine;
namespace std {
	template<class T, class D>
	class unique_ptr;
}

namespace BEbraEngine {

}

namespace BEbraEngine {
	class AngelScriptEngine : public BaseScriptEngine
	{
	public:
		AngelScriptEngine(IProxyGameObjectFactory* factory);

		~AngelScriptEngine();

		std::optional<AngelScript*> createScript(std::string path, std::string name);

		void executeScript(AngelScript* script, const std::string&& name);

		AngelScript* CreateScript(std::string code) override;
	private:

		asIScriptEngine* engine;
		IProxyGameObjectFactory* factory;
		
	};
}


