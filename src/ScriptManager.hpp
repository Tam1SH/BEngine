#pragma once

#include <map>
#include <string>
#include "GameComponent.hpp"
#include "BaseScript.hpp"
#include "BaseScriptEngine.hpp"
#include "AngelScriptEngine.hpp"
#include "AngelScript.hpp"

namespace BEbraEngine {
	class ObjectFactoryFacade;
}

namespace BEbraEngine {

	class ScriptManager
	{
	private:
		std::unique_ptr<AngelScriptEngine> engine;

		std::vector<std::shared_ptr<AngelScript>> scripts;

		std::shared_ptr<WorkSpace> workspace;

		ObjectFactoryFacade* factory;

	public:
		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		std::optional<std::shared_ptr<AngelScript>> getScriptByName(const std::string& name);

		void runScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager(ObjectFactoryFacade* factory);

		ScriptManager() {}

		~ScriptManager();

	};

}