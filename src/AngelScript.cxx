#include <angelscript.h>
module AngelScript;
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
	
	void AngelScript::destroy(GameComponentDestroyer& destroyer)
	{
	}
}
