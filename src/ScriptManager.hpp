#pragma once

#include <map>
//#include <filesystem>
#include <string>
#include "AbstractComponent.hpp"
#include "BaseScript.hpp"
#include "BaseScriptEngine.hpp"
namespace BEbraEngine {
	class WorkSpace;
	class ScriptManager
	{
	private:
		std::map<std::string, std::shared_ptr<BaseScriptEngine>> engines;
		std::map<std::string, std::shared_ptr<BaseScript>> scripts;

		std::shared_ptr<WorkSpace> workspace;
	private:

	public:
		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		std::shared_ptr<BaseScript> GetScriptByName(std::string name);

		void RunScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager();

		~ScriptManager();

	};

}