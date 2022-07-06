#include "platform.hpp"
#include <angelscript.h>
#include <boost/filesystem.hpp>
export module AngelScriptEngine;
import <optional>;
import <string>;
import AngelScript;
import Debug;
import BaseScriptEngine;
import ObjectFactoryFacade;


using std::optional;
using std::string;


namespace BEbraEngine {
	export class AngelScriptEngine final //: public BaseScriptEngine
	{
	public:
		AngelScriptEngine(ObjectFactoryFacade* factory);

		~AngelScriptEngine();

		std::optional<AngelScript*> createScript(string path, string name);

		void executeScript(AngelScript* script, const string&& name);

	private:

		asIScriptEngine* engine;

		ObjectFactoryFacade* factory;
		
	};
}


