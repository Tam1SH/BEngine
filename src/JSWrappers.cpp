#include "stdafx.h"
/*
#include "JSWrappers.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "Camera.hpp"
#include "v8pp/v8pp/class.hpp"
namespace BEbraEngine {
    JS_Vector3::JS_Vector3(float x, float y, float z)
    {
        vec.x = x;
        vec.y = y;
        vec.z = z;
    }

    JS_Vector3::operator glm::vec3& ()
    {
        return vec;
    }

    float JS_Vector3::GetX()
    {
        return vec.x;
    }


    JS_GameObject::JS_GameObject(JS_Vector3 vec, bool isParentScript)
    {
        if (!isParentScript)
            obj = GameObject::New(vec);
    }

    void JS_GameObject::SetObject(std::shared_ptr<GameObject> object)
    {
    }



    void JS_GameObject::Destroy()
    {
        GameObject::Destroy(obj);
        obj.reset();
    }

    v8::Local<v8::Value> JS_GameObject::GetComponent(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Isolate* isolate = info.GetIsolate();
        v8::HandleScope scope(isolate);
        v8::Local<v8::Value> arg = info[0];
        v8::String::Utf8Value value(isolate, arg);

        if (*value == "Transform") {
            auto comp_ = obj->GetComponent<Transform>();
            return v8pp::class_<Transform>
                ::reference_external(isolate, comp_);
        }
        if (*value == "RigidBody") {
            auto comp_ = obj->GetComponent<RigidBody>();
            return v8pp::class_<RigidBody>
                ::reference_external(isolate, comp_);
        }
        return v8::Local<v8::Value>();

    }

    JS_GameObject::~JS_GameObject()
    {

    }


    CameraWrapper::CameraWrapper()
    {
        camera = Camera::instance;
    }

    void CameraWrapper::Update()
    {
        camera->Update();
    }

    void JS_RunService::Connect(const v8::FunctionCallbackInfo<v8::Value>& function)
    {
        auto local_func = v8::Local<v8::Function>::Cast(function[0]);
        auto func = new v8::Persistent<v8::Function>(function.GetIsolate(), local_func);
        functions.push_back(func);
    }

    void JS_RunService::Start()
    {
        for (auto& func : functions) {
            auto local_context = isolate->GetCurrentContext();
            func->Get(isolate)->Call(local_context, local_context->Global(), 0, 0);
        }
    }

    Event::Event(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        auto _func = v8::Local<v8::Function>::Cast(info[0]);
        isolate = info.GetIsolate();
        func = new v8::Persistent<v8::Function>(info.GetIsolate(), _func);

        std::cout << "EBAT INIT" << "\n";
    }

    void Event::Execute()
    {
        auto local_context = isolate->GetCurrentContext();
        func->Get(isolate)->Call(local_context, local_context->Global(), 0, 0);
    }
}
*/