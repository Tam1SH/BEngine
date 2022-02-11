#pragma once
#include "BaseScript.hpp"
class asIScriptContext;

namespace BEbraEngine {

	class AngelScript final : public BaseScript
	{
	public:

		asIScriptContext* getContext();

		AngelScript(asIScriptContext* context);

		void destroy(IVisitorGameComponentDestroyer& destroyer) override;
		
	private:
		asIScriptContext* context;

		
	};
}

