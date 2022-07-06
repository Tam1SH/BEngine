#include <boost/filesystem.hpp>
export module ScriptManager;
import <map>;
import <string>;
import <optional>;
import <memory>;
import <vector>;
import ObjectFactoryFacade;
import AngelScriptEngine;
import AngelScript;
using std::string; 
using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
}

namespace BEbraEngine {

	export class ScriptManager
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