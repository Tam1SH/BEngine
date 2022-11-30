module;
#include <map>
#include <string>
#include <optional>
#include <memory>
#include <vector>
export module ScriptManager;


import AngelScriptEngine;
import AngelScript;
using std::string; 
using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
	export struct ObjectFactoryFacade;
}

namespace BEbraEngine {

	export struct ScriptManager {

		optional<shared_ptr<AngelScript>> getScriptByName(const string& name);

		void runScripts();

		void InitScripts();

		void LoadScripts();

		ScriptManager(ObjectFactoryFacade* factory);

		ScriptManager() {}

		~ScriptManager();

	private:
		AngelScriptEngine engine;

		std::vector<shared_ptr<AngelScript>> scripts;

		ObjectFactoryFacade* factory;
	};

}