#include "stdafx.h"
#include "ScriptManager.hpp"
#include "AngelScriptEngine.hpp"
#include <filesystem>
namespace BEbraEngine {
	

	void ScriptManager::SetWorkSpace(std::shared_ptr<WorkSpace> workspace)
	{
		ScriptManager::workspace = workspace;
	}
	std::optional<std::shared_ptr<AngelScript>> ScriptManager::getScriptByName(std::string name)
	{
		for (auto& script : scripts) {
			if (script->getName() == name) {
				return std::make_optional(script);
			}
		}
		return std::optional<std::shared_ptr<AngelScript>>();
	}
	void ScriptManager::runScripts()
	{
		tbb::parallel_for<size_t>(0, scripts.size(), [&](size_t i) {
			if (scripts[i]->getActive()) 
				engine->executeScript(scripts[i].get(), "Update");
			
		});
	}
	void ScriptManager::InitScripts()
	{
		tbb::parallel_for<size_t>(0, scripts.size(), [&](size_t i) {
			if (scripts[i]->getActive()) 
				engine->executeScript(scripts[i].get(), "Start");
			
			});
	}
	void ScriptManager::LoadScripts()
	{
		using namespace nlohmann;

		auto currentPath = std::filesystem::current_path();
		currentPath /= "scripts";
		auto setup = currentPath / "setup.json";
		std::ifstream stream(setup);
		json j;
		stream >> j;
		for (int i = 0; i < j["scripts"].size(); i++) {
			std::string name;
			std::string path;
			for (auto& [key, value] : j["scripts"][i].items()) {
				if (key == "name") {
					name = value;
				}
				if (key == "path") {
					path = value;
				}
			}
			auto opt_script = engine->createScript(path, name);

			if (opt_script.has_value()) {
				auto script = std::shared_ptr<AngelScript>(opt_script.value());
				script->SetActive(true);
				scripts.push_back(script);
			}
		}

		
	}
	ScriptManager::ScriptManager(IProxyGameObjectFactory* factory)
	{
		this->factory = factory;
		engine = std::unique_ptr<AngelScriptEngine>(new AngelScriptEngine(factory));

	}

	ScriptManager::~ScriptManager()
	{
		for (auto& script : scripts) {
			script->destroy();
		}
	}
}