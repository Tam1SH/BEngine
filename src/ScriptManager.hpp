#pragma once

#include <map>
#include <string>
#include "AbstractComponent.hpp"
#include "BaseScript.hpp"
#include "BaseScriptEngine.hpp"
#include "AngelScriptEngine.hpp"
#include "AngelScript.hpp"
#include "IProxyGameObjectFactory.hpp"
namespace BEbraEngine {
	class WorkSpace;
	class ScriptManager
	{
	private:
		std::unique_ptr<AngelScriptEngine> engine;

		std::vector<std::shared_ptr<AngelScript>> scripts;

		std::shared_ptr<WorkSpace> workspace;

		IProxyGameObjectFactory* factory;

	public:
		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		std::optional<std::shared_ptr<AngelScript>> getScriptByName(std::string name);

		void runScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager(IProxyGameObjectFactory* factory);

		ScriptManager() {}

		~ScriptManager();

	};

}