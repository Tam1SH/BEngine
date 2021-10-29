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
		std::map<std::wstring, std::shared_ptr<IScriptFactory>> engines;
		std::map<std::wstring, std::shared_ptr<BaseScript>> scripts;

		std::shared_ptr<WorkSpace> workspace;
	private:
		//void AddScript(const std::filesystem::path& path, const wchar_t* engineName);

	public:
		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		std::shared_ptr<BaseScript> GetScriptByName(std::wstring name);

		void RunScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager();

		~ScriptManager();

	};

}