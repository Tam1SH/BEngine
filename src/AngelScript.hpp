#pragma once
#include "BaseScript.hpp"
class asIScriptContext;

namespace BEbraEngine {

	class AngelScript final : public BaseScript
	{
	public:

		virtual void init() override;
		virtual void run() override;
		virtual void destroy() override;
		asIScriptContext* getContext();
		AngelScript(asIScriptContext* context);

		void destroy(IVisitorGameComponentDestroyer& destroyer) override;
		
	private:
		asIScriptContext* context;

		
	};
}

