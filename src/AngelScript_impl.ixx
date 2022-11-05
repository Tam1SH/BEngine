#include <angelscript.h>
export module AngelScript_impl;
import AngelScript;
//import GameComponentDestroyer;
namespace BEbraEngine {

	asIScriptContext* AngelScript::getContext()
	{
		return context;
	}

	AngelScript::AngelScript(asIScriptContext* context)
	{
		this->context = context;
	}
	
}
