#pragma once
#include "BaseScript.hpp"
class asIScriptContext;

namespace BEbraEngine {

	class AngelScript : public BaseScript
	{
	public:
		virtual void init() override;
		virtual void run() override;
		virtual void destroy() override;
		asIScriptContext* getContext();
		AngelScript(asIScriptContext* context);
		
	private:
		asIScriptContext* context;
	};
}

