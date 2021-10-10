/*
#include "JScriptEngine.hpp"
#include "include/libplatform/libplatform.h"

#include <string>
#include <iostream>
#include <filesystem>


#include "v8pp/v8pp/module.hpp"
#include "v8pp/v8pp/class.hpp"
#include "v8pp/v8pp/context.hpp"

#include "JSWrappers.hpp"
#include "JScript.hpp"
namespace BEbraEngine {
    void JScriptEngine::logger(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        if (info.Length() < 1) return;
        v8::Isolate* isolate = info.GetIsolate();
        v8::HandleScope scope(isolate);
        v8::Local<v8::Value> arg = info[0];
        v8::String::Utf8Value value(isolate, arg);

        printf(*value);

    }


    JScriptEngine::JScriptEngine(char* path)
    {
        v8::V8::InitializeICUDefaultLocation(path);
        v8::V8::InitializeExternalStartupData(path);
        platform = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(platform.get());
        v8::V8::Initialize();
    }

    v8::Handle<v8::ObjectTemplate> JScriptEngine::SetDefaultGlobalContext(v8::Isolate* isolate)
    {
        v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

        global->Set(v8::String::NewFromUtf8(isolate, "print").ToLocalChecked(),
            v8::FunctionTemplate::New(isolate, logger));

        return global;
    }
    void print(const glm::vec3& pos) {
        std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << std::endl;
    }
    void JScriptEngine::InitGlobalContext(v8::Isolate* isolate) {
        v8pp::module mylib(isolate);


        v8pp::class_<CameraWrapper> camera(isolate);
        camera.ctor<>()
            .set("Update", &CameraWrapper::Update);

        v8pp::class_<JS_GameObject> gameObject(isolate);
        gameObject.ctor<JS_Vector3>()
            .set("Destroy", &JS_GameObject::Destroy);

        v8pp::class_<JS_Vector3> vector(isolate);
        vector.ctor<float, float, float>()
            .set("x", v8pp::property(&JS_Vector3::GetX, &JS_Vector3::SetX))
            .set("y", v8pp::property(&JS_Vector3::GetY, &JS_Vector3::SetY))
            .set("z", v8pp::property(&JS_Vector3::GetZ, &JS_Vector3::SetZ));

        v8pp::class_<JS_RunService> runService(isolate);
        runService.set("Connect", &JS_RunService::Connect);
        mylib.set("RunService", runService);
        mylib.set("Vector3", vector);
        mylib.set("GameObject", gameObject);
        mylib.set("Camera", camera);

        auto global = isolate->GetCurrentContext()->Global();

        global->Set(isolate->GetCurrentContext(),
            v8::String::NewFromUtf8(isolate, "BEbraEngine").ToLocalChecked(),
            mylib.new_instance());

    }
    v8::Local<v8::Module> JScriptEngine::CreateModule(std::string code, v8::Isolate* isolate) {


        v8::Local<v8::String> source_text = v8::String::NewFromUtf8(
            isolate, code.c_str())
            .ToLocalChecked();

        v8::TryCatch tc(isolate);


        v8::ScriptOrigin origin(
            isolate,
            v8::String::NewFromUtf8(isolate, "./BEbraCore").ToLocalChecked(),
            0,
            0,
            0,
            0,
            v8::Local<v8::Value>(),
            0,
            0,
            true);

        v8::Context::Scope context_scope1(isolate->GetCurrentContext());
        v8::ScriptCompiler::Source source1(source_text, origin);

        v8::Local<v8::Module> synthetic_module;

        v8::TryCatch trycatch(isolate);

        if (!v8::ScriptCompiler::CompileModule(isolate, &source1).ToLocal(&synthetic_module)) {

            v8::Local<v8::Value> except = trycatch.Exception();
            v8::String::Utf8Value except_str = v8::String::Utf8Value(isolate, except);
            printf("Exception: %s\n", *except_str);


        }

        synthetic_module->InstantiateModule(isolate->GetCurrentContext(),
            [](v8::Local<v8::Context> context,
                v8::Local<v8::String> specifier,
                v8::Local<v8::Module> referrer) {

                    return v8::MaybeLocal<v8::Module>();
            });
        v8::Local<v8::Value> result;


        ////if (synthetic_module->Evaluate(isolate->GetCurrentContext()).ToLocal(&result)) {
        //    String::Utf8Value utf8(isolate, result);
        //}

        return synthetic_module;
    }
    BaseScript* JScriptEngine::CreateScript(std::string code)
    {

        v8::Isolate::CreateParams create_params;
        create_params.array_buffer_allocator =
            v8::ArrayBuffer::Allocator::NewDefaultAllocator();

        v8::Isolate* isolate = v8::Isolate::New(create_params);

        v8::Isolate::Scope isolate_scope(isolate);
        v8::HandleScope handle_scope{ isolate };

        v8::Local<v8::Context> local_context = v8::Context::New(isolate, 0, SetDefaultGlobalContext(isolate));

        v8::Persistent<v8::Context>* global_context = new v8::Persistent<v8::Context>();

        global_context->Persistent::Persistent(isolate, local_context);
        v8::Context::Scope* context_scope = new v8::Context::Scope(global_context->Get(isolate));

        InitGlobalContext(isolate);

        v8::Local<v8::String> source_text = v8::String::NewFromUtf8(
            isolate, code.c_str())
            .ToLocalChecked();

        v8::TryCatch tc(isolate);
        v8::Persistent<v8::Module>* scr = 0;

        v8::TryCatch trycatch(isolate);

        v8::ScriptOrigin origin(v8::String::NewFromUtf8(isolate, "hello_world").ToLocalChecked(),
            v8::Integer::New(isolate, 0),
            v8::Integer::New(isolate, 0),
            v8::False(isolate),
            v8::Local<v8::Integer>(),
            v8::Local<v8::Value>(),
            v8::False(isolate),
            v8::False(isolate),
            v8::True(isolate));



        v8::Local<v8::Module> module;// = Script::Compile(local_context, source_text).ToLocalChecked();

        v8::ScriptCompiler::Source source1(source_text, origin);

        if (!v8::ScriptCompiler::CompileModule(isolate, &source1).ToLocal(&module)) {
            v8::Local<v8::Value> except = trycatch.Exception();
            v8::String::Utf8Value except_str = v8::String::Utf8Value(isolate, except);
            printf("Exception: %s\n", *except_str);
        }

        static JScriptEngine* self;
        static v8::Persistent<v8::Module>* mainModule;
        self = this;
        module->InstantiateModule(global_context->Get(isolate),
            [](v8::Local<v8::Context> context,
                v8::Local<v8::String> specifier,
                v8::Local<v8::Module> referrer) {
                    JScriptEngine* pizda = self;
                    auto code = pizda->DownloadScript(std::filesystem::current_path() / "scripts\\BEbraCore.js");
                    auto module = pizda->CreateModule(code, context->GetIsolate());
                    mainModule = new v8::Persistent<v8::Module>(context->GetIsolate(), module);
                    std::cout << *v8::String::Utf8Value(context->GetIsolate(), specifier);
                    return v8::MaybeLocal<v8::Module>(module);
            });


        scr = new v8::Persistent<v8::Module>();
        scr->v8::Persistent<v8::Module>::Persistent(isolate, module);



        delete create_params.array_buffer_allocator;

        return new JScript(isolate, mainModule, scr);
    }

    JScriptEngine::~JScriptEngine()
    {

        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
    }
}
*/