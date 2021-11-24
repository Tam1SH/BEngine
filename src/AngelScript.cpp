#include "stdafx.h"
#include "AngelScript.hpp"
#include <angelscript.h>
namespace BEbraEngine {

	void AngelScript::Initialization()
	{
	}

	void AngelScript::Run()
	{
	}

	void AngelScript::Destroy()
	{
	}
	AngelScript::AngelScript(asIScriptContext* context)
	{
		this->context = context;
	}
}
