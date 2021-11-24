#pragma once
#include "BaseScript.hpp"
class asIScriptContext;

namespace BEbraEngine {

	class AngelScript : public BaseScript
	{
	public:
		virtual void Initialization() override;
		virtual void Run() override;
		virtual void Destroy() override;
		AngelScript(asIScriptContext* context);
	private:
		asIScriptContext* context;
	};
}

