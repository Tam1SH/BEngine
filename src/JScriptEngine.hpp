#pragma once
/*

#include "BaseScript.hpp"
#include "BaseScriptEngine.hpp"
#include <memory>
#include <v8.h>
namespace BEbraEngine {
    class JScriptEngine : public BaseScriptEngine
    {
    private:
        friend class JScript;
    private:
        std::unique_ptr<v8::Platform> platform;
    private:

        static void logger(const v8::FunctionCallbackInfo<v8::Value>& info);

        v8::Handle<v8::ObjectTemplate> SetDefaultGlobalContext(v8::Isolate* isolate);

        void InitGlobalContext(v8::Isolate* isolate);

    public:
        JScriptEngine(char* path);

        v8::Local<v8::Module> CreateModule(std::string code, v8::Isolate* isolate);

        BaseScript* CreateScript(std::string code) override;

        ~JScriptEngine();

    };
}
*/
