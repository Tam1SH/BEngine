#include "stdafx.h"
#include "AngelScript.hpp"
#include <angelscript.h>
namespace BEbraEngine {

	void AngelScript::init()
	{
	}

	void AngelScript::run()
	{
	}

	void AngelScript::destroy()
	{
	}
	AngelScript::AngelScript(asIScriptContext* context)
	{
		this->context = context;
	}
}
