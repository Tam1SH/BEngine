module;
#include "platform.hpp"
#include <angelscript.h>
#include <optional>
#include <string>
export module AngelScriptEngine;
import AngelScript;
import BaseScriptEngine;


using std::optional;
using std::string;
namespace BEbraEngine {
	export struct ObjectFactoryFacade;
}

namespace BEbraEngine {
	export class AngelScriptEngine final //: public BaseScriptEngine
	{
	public:

		std::optional<AngelScript*> createScript(string path, string name);

		void executeScript(AngelScript* script, const string& name);

		AngelScriptEngine(ObjectFactoryFacade* factory);

		AngelScriptEngine() {}

		~AngelScriptEngine();

	private:

		asIScriptEngine* engine;

		ObjectFactoryFacade* factory;
		
	};
}


