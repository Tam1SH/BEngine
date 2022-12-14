module;
#include <angelscript.h>
export module AngelScript;
import BaseScript;

namespace BEbraEngine {

	export struct AngelScript : BaseScript 
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

