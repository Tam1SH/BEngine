#include "stdafx.h"
#include <angelscript.h>
#include "AngelScriptEngine.hpp"
#include "Debug.hpp"

#include <add_on/scriptstdstring/scriptstdstring.h>
#include <add_on/scriptbuilder/scriptbuilder.h>
#include <add_on/weakref/weakref.h>
#include <add_on/scripthandle/scripthandle.h>
#include "AngelScript.hpp"
#include "ScriptWrappers.hpp"
namespace BEbraEngine {
	void MessageCallback(const asSMessageInfo& msg) {
		const char* type = "ERR ";
		if (msg.type == asMSGTYPE_WARNING)
			type = "WARN";
		else if (msg.type == asMSGTYPE_INFORMATION)
			type = "INFO";

		std::cout << msg.section << " (" << msg.row << ", " << msg.col << ") : " << type << " : " << msg.message << std::endl;

	}
	void print(const std::string& in) {
		std::cout << in << std::endl;
	}
	void print(const float& in) {
		std::cout << in << std::endl;
	}

	AngelScriptEngine::AngelScriptEngine(IProxyGameObjectFactory* factory)
	{
		this->factory = factory;

		engine = asCreateScriptEngine();

		RegisterStdString(engine);

		RegisterScriptHandle(engine);
		RegisterScriptWeakRef(engine);

		int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(print, (const std::string&), void), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("void print(float &in)", asFUNCTIONPR(print, (const float&), void), asCALL_CDECL); assert(r >= 0);


		Wrappers::_Vector3::registerObj(engine);
		Wrappers::_GameObject::registerObj(engine);
		Wrappers::_GameObject::factory = factory;
	}

	AngelScriptEngine::~AngelScriptEngine()
	{
		engine->ShutDownAndRelease();
	}


	std::optional<AngelScript*> AngelScriptEngine::createScript(std::string path, std::string name) {

		CScriptBuilder builder;
		builder.StartNewModule(engine, name.c_str());
		builder.AddSectionFromFile(path.c_str());
		int r = builder.BuildModule();
		if (r < 0) {
			Debug::log("Can't create a script. Params : " + path + " | " + name, 0, 
				"ScriptEngine", Debug::ObjectType::Script, Debug::MessageType::Error);
			return std::make_optional<AngelScript*>();
		}
		asIScriptContext* ctx = engine->CreateContext();
		auto script = new AngelScript(ctx);
		script->setName(name);
		return std::make_optional<AngelScript*>(script);
	}
	void AngelScriptEngine::executeScript(AngelScript* script, const std::string&& name)
	{

		asIScriptModule* mod = engine->GetModule(script->getName().c_str());
		asIScriptFunction* func = mod->GetFunctionByName(name.c_str());
		if (func == 0)
		{
			std::string xyuuuu = "The script must have the function '";
			printf((xyuuuu + name + "'. Please add it and try again.\n").c_str());
			return;
		}

		asIScriptContext* ctx = engine->CreateContext();
		ctx->Prepare(func);
		int r = ctx->Execute();
		if (r != asEXECUTION_FINISHED)
		{
			if (r == asEXECUTION_EXCEPTION)
			{
				printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
			}
		}

		ctx->Release();
	}
	AngelScript* AngelScriptEngine::CreateScript(std::string code)
	{
		return nullptr;
	}
}

