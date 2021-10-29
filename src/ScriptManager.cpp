#include "stdafx.h"
#include "ScriptManager.hpp"

#include "LuaEngine.hpp"
//#include "PythonEngine.hpp"
#include "JScriptEngine.hpp"

//TODO: стал бесполезен.
namespace BEbraEngine {
	constexpr const wchar_t* LUA = L"LUA";
	constexpr const wchar_t* PYTHON = L"PYTHON";
	constexpr const wchar_t* JAVASCRIPT = L"JAVASCRIPT";

	//void ScriptManager::AddScript(const std::filesystem::path& path, const wchar_t* engineName)
	//{
		//std::wstring name = path.filename();
		//auto code = engines[engineName]->DownloadScript(path);
		//scripts[name] = std::shared_ptr<BaseScript>(engines[engineName]->CreateScript(code));
	//}
	void ScriptManager::SetWorkSpace(std::shared_ptr<WorkSpace> workspace)
	{
		ScriptManager::workspace = workspace;
	}
	std::shared_ptr<BaseScript> ScriptManager::GetScriptByName(std::wstring name)
	{
		return scripts[name];
	}
	void ScriptManager::RunScripts()
	{
		for (auto& script : scripts) {
			if (script.second->GetActive())
				script.second->Run();
		}
	}
	void ScriptManager::InitScripts()
	{
		BaseScript::SetWorkSpace(workspace);
		for (auto& script : scripts) {
			if (script.second->GetActive())
				script.second->Initialization();
		}
	}
	void ScriptManager::LoadScripts()
	{
		/*
		auto currentPath = std::filesystem::current_path();
		currentPath /= "scripts";

		for (auto& files : std::filesystem::directory_iterator(currentPath)) {
			auto extension = files.path().extension();
			if (extension == ".js") {
				AddScript(files.path(), JAVASCRIPT);
			}
			if (extension == ".lua") {
				AddScript(files.path(), LUA);
			}
			if (extension == ".py") {
				AddScript(files.path(), PYTHON);
			}
		}
		*/
	}
	ScriptManager::ScriptManager()
	{
		//std::wstring s = std::filesystem::current_path().c_str();
		//std::string st{ s.begin(), s.end() };


		//engines[LUA] = std::shared_ptr<IScriptFactory>(new LuaEngine());
		//engines[JAVASCRIPT] = std::shared_ptr<IScriptFactory>(
			//new JScriptEngine(const_cast<char*>(st.c_str())));


	}

	ScriptManager::~ScriptManager()
	{
		for (auto& script : scripts) {
			script.second->Destroy();
		}
	}
}