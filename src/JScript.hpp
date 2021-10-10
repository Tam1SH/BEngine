#pragma once
/*
#include <v8.h>
#include "BaseScript.hpp"
#include "JSWrappers.hpp"
namespace BEbraEngine {
    class JScriptEngine;
    class JScript : public BaseScript {
    private:
        friend class JScriptEngine;
    private:
        v8::Persistent<v8::Module>* mainModule;

        v8::Persistent<v8::Module>* currentModule;

        v8::Isolate* isolate;

        JS_RunService* runService;

        JS_GameObject* wrapParent;

    private:
        v8::Local<v8::Function> GetGlobalFunction(std::string name);

        void pizda();

    public:
        JScript(v8::Isolate* isolate,
            v8::Persistent<v8::Module>* mainModule,
            v8::Persistent<v8::Module>* currentModule);


        void Initialization() override;

        void Run() override;

        void Destroy() override;

    };
}
*/

