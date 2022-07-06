#include <angelscript.h>
export module AngelScript;

import BaseScript;
import IVisitorGameComponentDestroyer;

namespace BEbraEngine {

	export class AngelScript final : public BaseScript
	{
	public:

		asIScriptContext* getContext();

		AngelScript(asIScriptContext* context);

		void destroy(IVisitorGameComponentDestroyer& destroyer) { } //override;
		
	private:
		asIScriptContext* context;

		
	};
}

