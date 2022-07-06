#include <angelscript.h>
module AngelScript;
namespace BEbraEngine {

	asIScriptContext* AngelScript::getContext()
	{
		return context;
	}
	AngelScript::AngelScript(asIScriptContext* context)
	{
		this->context = context;
	}
	//void AngelScript::destroy(IVisitorGameComponentDestroyer& destroyer)
	//{
	//}
}
