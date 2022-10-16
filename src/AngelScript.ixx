module;
#include <angelscript.h>
export module AngelScript;
import BaseScript;
import GameComponentDestroyerDecl;

namespace BEbraEngine {

	export class AngelScript final : public BaseScript 
	{
	public:

		void destroy(GameComponentDestroyer& destroyer) override;

		asIScriptContext* getContext();

		AngelScript(asIScriptContext* context);
		
	private:
		asIScriptContext* context;
	};
}

