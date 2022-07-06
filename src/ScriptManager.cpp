#include <boost/filesystem.hpp>
#include <tbb.h>
#include <filesystem>
#include <json.hpp>
#include <fstream>
module ScriptManager;
import Time;

import AngelScriptEngine;
using std::optional;
using std::shared_ptr;
using std::string;
using std::unique_ptr;

namespace BEbraEngine {
	


	optional<shared_ptr<AngelScript>> ScriptManager::getScriptByName(const string& name)
	{
		for (auto& script : scripts) {
			if (script->getName() == name) {
				return std::make_optional(script);
			}
		}
		return optional<shared_ptr<AngelScript>>();
	}
	/// <summary>
	///  Вызывает все события в активных скриптах.
	/// </summary>
	void ScriptManager::runScripts()
	{
		static float time = 0.f;
		
		tbb::task_group task;
		task.run([&] {
			tbb::parallel_for<size_t>(0, scripts.size(), [&](size_t i) {
				//for (int i = 0; i < scripts.size(); i++) {
				if (scripts[i]->getActive())
					engine->executeScript(scripts[i].get(), "Update");
			}
			);
		});
		time += Time::deltaTime();
		if (time >= Time::fixedDeltaTime())
			task.run([&] {
			tbb::parallel_for<size_t>(0, scripts.size(), [&](size_t i) {
				//for (int i = 0; i < scripts.size(); i++) {
				if (scripts[i]->getActive())
					engine->executeScript(scripts[i].get(), "FixedUpdate");
			}
			);
		});
		task.wait();
	}
	void ScriptManager::InitScripts()
	{
		tbb::parallel_for<size_t>(0, scripts.size(), [&](size_t i) {
			if (scripts[i]->getActive()) 
				engine->executeScript(scripts[i].get(), "Start");
			
			});
	}
	/// <summary>
	/// Загружает все скрипты, указанные в жсон файле. 
	/// </summary>
	void ScriptManager::LoadScripts()
	{
		using namespace nlohmann;

		try {


			auto currentPath = std::filesystem::current_path();
			currentPath /= "scripts";
			auto setup = currentPath / "setup.json";
			std::ifstream stream(setup);
			json j;
			stream >> j;
			for (int i = 0; i < j["scripts"].size(); i++) {
				string name;
				string path;
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
		catch (std::exception& ex) {
			//DEBUG_LOG1(ex.what());
		}

		
	}
	ScriptManager::ScriptManager(ObjectFactoryFacade* factory)
	{
		this->factory = factory;
		engine = unique_ptr<AngelScriptEngine>(new AngelScriptEngine(factory));

	}

	ScriptManager::~ScriptManager()
	{
		for (auto& script : scripts) {
			//script->destroy();
		}
	}
}