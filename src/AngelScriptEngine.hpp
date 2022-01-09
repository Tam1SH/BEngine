#pragma once
#include "stdafx.h"
#include "BaseScriptEngine.hpp"
#include "AngelScript.hpp"

class asIScriptEngine;
namespace std {
	template<class T, class D>
	class unique_ptr;
}

namespace BEbraEngine {
	class ObjectFactoryFacade;
}

namespace BEbraEngine {
	class AngelScriptEngine final : public BaseScriptEngine
	{
	public:
		AngelScriptEngine(ObjectFactoryFacade* factory);

		~AngelScriptEngine();

		std::optional<AngelScript*> createScript(std::string path, std::string name);

		void executeScript(AngelScript* script, const std::string&& name);

		AngelScript* CreateScript(std::string code) override;
	private:

		asIScriptEngine* engine;

		ObjectFactoryFacade* factory;
		
	};
}


