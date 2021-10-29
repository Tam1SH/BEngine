#include "stdafx.h"
/*
#include "JScript.hpp"
#include <iostream>
#include "v8pp/v8pp/class.hpp"
#include "v8pp/v8pp/module.hpp"
namespace BEbraEngine {
    v8::Local<v8::Function> JScript::GetGlobalFunction(std::string name)
    {
        auto local_context = isolate->GetCurrentContext();
        v8::Local<v8::Object> global = local_context->Global();
        v8::Local<v8::Value> value = global->Get(local_context, v8::String::NewFromUtf8(isolate, name.c_str()).ToLocalChecked()).ToLocalChecked();
        if (value->IsFunction()) {
            v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(value);
            return func;
        }
        else
        {
            v8::String::Utf8Value utf8(isolate, value);
            std::cout << *utf8 << std::endl;
        }


    }

    void JScript::pizda()
    {
        v8pp::module localScript(isolate);

        runService = new JS_RunService(isolate);

        auto _parent = workspace->FindObject(this->GetParent());
        wrapParent = new JS_GameObject(JS_Vector3(0, 0, 0), true);
        wrapParent->SetObject(_parent);

        v8::Local<v8::Value> _runService = v8pp::class_<JS_RunService>::reference_external(isolate, runService);
        v8::Local<v8::Value> parent = v8pp::class_<JS_GameObject>::reference_external(isolate, wrapParent);

        auto instance = localScript.new_instance();
        auto global = isolate->GetCurrentContext()->Global();

        global->Set(isolate->GetCurrentContext(),
            v8::String::NewFromUtf8(isolate, "__LOCAL_SCRIPT__").ToLocalChecked(),
            instance);
        instance->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_RunService").ToLocalChecked(), _runService);
        instance->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_parent").ToLocalChecked(), _runService);
    }

    JScript::JScript(v8::Isolate* isolate, v8::Persistent<v8::Module>* mainModule, v8::Persistent<v8::Module>* currentModule) :
        isolate(isolate),
        mainModule(mainModule),
        currentModule(currentModule)
    { }

    void JScript::Initialization()
    {

        v8::HandleScope handle_scope{ isolate };
        // isolate->Enter();
        v8::TryCatch trycatch(isolate);

        pizda();

        v8::Local<v8::Value> result;
        if (mainModule->Get(isolate)->Evaluate(isolate->GetCurrentContext()).ToLocal(&result)) {
            v8::String::Utf8Value utf8(isolate, result);
            printf("script init: %s\n", *utf8);
        }
        if (currentModule->Get(isolate)->Evaluate(isolate->GetCurrentContext()).ToLocal(&result)) {
            v8::String::Utf8Value utf8(isolate, result);
            printf("script init: %s\n", *utf8);
        }


        if (result.IsEmpty()) {
            v8::Local<v8::Value> except = trycatch.Exception();
            v8::String::Utf8Value except_str = v8::String::Utf8Value(isolate, except);
            printf("Exception: %s\n", *except_str);

        }

    }

    void JScript::Run()
    {

        v8::HandleScope handle_scope{ isolate };
        isolate->Enter();

        v8::TryCatch trycatch(isolate);

        runService->Start();

        v8::Local<v8::Value> except = trycatch.Exception();
        if (!except.IsEmpty()) {
            v8::String::Utf8Value except_str = v8::String::Utf8Value(isolate, except);
            printf("Exception: %s\n", *except_str);
        }



        isolate->Exit();
    }

    void JScript::Destroy()
    {
        v8pp::cleanup(isolate);
        isolate->Dispose();
        delete runService;
    }
}
*/