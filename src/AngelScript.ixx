module;
#include <angelscript.h>
export module AngelScript;
import BaseScript;

namespace BEbraEngine {

	export class AngelScript final : public BaseScript 
	{
	public:

		template<typename Destroyer>
		void destroy(Destroyer& destroyer) {
			//destroyer.destroyLight(*this);
		}

		asIScriptContext* getContext();

		AngelScript(asIScriptContext* context);
		
	private:
		asIScriptContext* context;
	};
}

