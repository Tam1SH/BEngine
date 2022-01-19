#include "stdafx.h"
#include <angelscript.h>
#include "AngelScriptEngine.hpp"
#include "Debug.hpp"

#include <add_on/scriptstdstring/scriptstdstring.h>
#include <add_on/scriptbuilder/scriptbuilder.h>
#include <add_on/weakref/weakref.h>
#include <add_on/scripthandle/scripthandle.h>
#include <add_on/scriptarray/scriptarray.h>
#include "AngelScript.hpp"
#include "ScriptWrappers.hpp"
namespace BEbraEngine {
	
	static void MessageCallback(const asSMessageInfo& msg) {
		const char* type = "ERROR";
		if (msg.type == asMSGTYPE_WARNING)
			type = "WARN";
		else if (msg.type == asMSGTYPE_INFORMATION)
			type = "INFO";
		std::stringstream ss;
		ss << msg.section << " (" << msg.row << ", " << msg.col << ") : " << type << " : " << msg.message;
		DEBUG_LOG1(ss.str());

	}
	static void print(const std::string& in) {
		std::cout << in << std::endl;
	}
	static void print(const float& in) {
		std::cout << in << std::endl;
	}

	AngelScriptEngine::AngelScriptEngine(ObjectFactoryFacade* factory)
	{
		this->factory = factory;

		engine = asCreateScriptEngine();

		RegisterStdString(engine);

		RegisterScriptHandle(engine);
		RegisterScriptWeakRef(engine);
		RegisterScriptArray(engine,false);
		int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(print, (const std::string&), void), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void print(float &in)", asFUNCTIONPR(print, (const float&), void), asCALL_CDECL); assert(r >= 0);


		Wrappers::_Vector3::registerObj(engine);
		Wrappers::_GameObjectComponent::registerObj(engine);
		Wrappers::_GameObject::registerObj(engine);
		Wrappers::_Input::registerObj(engine);
		Wrappers::_Input::getInstance();
		
		Wrappers::_GameObject::factory = static_cast<ObjectFactoryFacade*>(factory);
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
			DEBUG_LOG2("Can't create a script. Params : " + path + " | " + name, 0, 
				"ScriptEngine", Debug::ObjectType::Script, Debug::MessageType::Error);
			return std::optional<AngelScript*>();
		}
		asIScriptContext* ctx = engine->CreateContext();
		auto script = new AngelScript(ctx);
		script->setName(name);
		return std::optional<AngelScript*>(script);
	}
	void AngelScriptEngine::executeScript(AngelScript* script, const std::string&& name)
	{

		asIScriptModule* mod = engine->GetModule(script->getName().c_str());
		asIScriptFunction* func = mod->GetFunctionByName(name.c_str());
		if (func == 0)
		{
			return;
		}
		
		asIScriptContext* ctx = script->getContext();
		
		ctx->Prepare(func);
		int r = ctx->Execute();
		if (r != asEXECUTION_FINISHED && r == asEXECUTION_EXCEPTION)
		{
			std::stringstream ss;
			ss << "ScriptException: ";
			ss << ctx->GetExceptionString();
			DEBUG_LOG2(ss.str(), script, script->getName(), Debug::ObjectType::Script, Debug::MessageType::Error);
		}
	}
	AngelScript* AngelScriptEngine::CreateScript(std::string code)
	{
		throw std::exception();
		return nullptr;
	}
}

