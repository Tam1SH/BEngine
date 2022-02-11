#pragma once
#include "platform.hpp"

#include "stdafx.h"

#include "BaseScriptEngine.hpp"
#include "AngelScript.hpp"

class asIScriptEngine;


BE_NAMESPACE_STD_BEGIN
	
	template<class T, class D>
	class unique_ptr;

BE_NAMESPACE_STD_END

using BE_STD::optional;
using BE_STD::string;

namespace BEbraEngine {
	class ObjectFactoryFacade;
}

namespace BEbraEngine {
	class AngelScriptEngine final : public BaseScriptEngine
	{
	public:
		AngelScriptEngine(ObjectFactoryFacade* factory);

		~AngelScriptEngine();

		optional<AngelScript*> createScript(string path, string name);

		void executeScript(AngelScript* script, const string&& name);

		AngelScript* CreateScript(string code) override;
	private:

		asIScriptEngine* engine;

		ObjectFactoryFacade* factory;
		
	};
}


