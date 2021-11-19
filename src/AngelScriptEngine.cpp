#include "stdafx.h"
#include "AngelScriptEngine.hpp"

#include <angelscript.h>
//#include <add_on/scriptstdstring/scriptstdstring.h>
//#include <add_on/scriptbuilder/scriptbuilder.h>

namespace BEbraEngine {
	void  MessageCallback(const std::string& in) {
		std::cout << in << std::endl;
	}
	void  print(const std::string& in) {
		std::cout << in << std::endl;
	}
	AngelScriptEngine::AngelScriptEngine()
	{
		/*
		asIScriptEngine* engine = asCreateScriptEngine();

		int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(r >= 0);

		// AngelScript doesn't have a built-in string type, as there is no definite standard 
		// string type for C++ applications. Every developer is free to register its own string type.
		// The SDK do however provide a standard add-on for registering a string type, so it's not
		// necessary to implement the registration yourself if you don't want to.
		RegisterStdString(engine);
		r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL); assert(r >= 0);

		CScriptBuilder builder;
		r = builder.StartNewModule(engine, "MyModule");
		if (r < 0)
		{
			// If the code fails here it is usually because there
			// is no more memory to allocate the module
			printf("Unrecoverable error while starting a new module.\n");
			return;
		}
		r = builder.AddSectionFromFile("scripts/test.as");
		if (r < 0)
		{
			// The builder wasn't able to load the file. Maybe the file
			// has been removed, or the wrong name was given, or some
			// preprocessing commands are incorrectly written.
			printf("Please correct the errors in the script and try again.\n");
			return;
		}
		r = builder.BuildModule();
		
		if (r < 0)
		{
			// An error occurred. Instruct the script writer to fix the 
			// compilation errors that were listed in the output stream.
			printf("Please correct the errors in the script and try again.\n");
			return;
		}
		// Find the function that is to be called. 
		asIScriptModule* mod = engine->GetModule("MyModule");
		asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
		if (func == 0)
		{
			// The function couldn't be found. Instruct the script writer
			// to include the expected function in the script.
			printf("The script must have the function 'void main()'. Please add it and try again.\n");
			return;
		}

		// Create our context, prepare it, and then execute
		asIScriptContext* ctx = engine->CreateContext();
		ctx->Prepare(func);
		r = ctx->Execute();
		if (r != asEXECUTION_FINISHED)
		{
			// The execution didn't complete as expected. Determine what happened.
			if (r == asEXECUTION_EXCEPTION)
			{
				// An exception occurred, let the script writer know what happened so it can be corrected.
				printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
			}
		}

		ctx->Release();
		engine->ShutDownAndRelease();
		*/
	}
	BaseScript* AngelScriptEngine::CreateScript(std::string code)
	{
		return nullptr;
	}
}

