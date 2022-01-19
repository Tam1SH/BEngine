#pragma once

#include <map>
#include <string>
#include "GameComponent.hpp"
#include "BaseScript.hpp"
#include "BaseScriptEngine.hpp"
#include "AngelScriptEngine.hpp"
#include "AngelScript.hpp"

using std::string; 
using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
	class ObjectFactoryFacade;
}

namespace BEbraEngine {

	class ScriptManager
	{
	private:
		unique_ptr<AngelScriptEngine> engine;

		std::vector<shared_ptr<AngelScript>> scripts;

		ObjectFactoryFacade* factory;

	public:

		optional<shared_ptr<AngelScript>> getScriptByName(const string& name);

		void runScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager(ObjectFactoryFacade* factory);

		ScriptManager() {}

		~ScriptManager();

	};

}