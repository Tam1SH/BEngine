#include <angelscript.h>
export module AngelScript;

import BaseScript;

namespace BEbraEngine {

	export class AngelScript final : public BaseScript
	{
	public:

		asIScriptContext* getContext();

		AngelScript(asIScriptContext* context);

		//void destroy(VisitorGameComponentDestroyer& destroyer) { } //override;
		
	private:
		asIScriptContext* context;

		
	};
}

