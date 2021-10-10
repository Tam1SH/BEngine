#pragma once
/*
#include <glm/glm.hpp>
#include <memory>
#include "Transform.hpp"
#include <v8.h>

namespace BEbraEngine {
    class Event;
    class JS_RunService {
        std::list<v8::Persistent<v8::Function>*> functions;

        v8::Isolate* isolate;
    public:
        JS_RunService(v8::Isolate* isolate) {
            this->isolate = isolate;
        }
        void Connect(const v8::FunctionCallbackInfo<v8::Value>& function);

        void Start();

    };
    class Event {
    private:
        v8::Persistent<v8::Function>* func;

        v8::Isolate* isolate;
    public:
        Event() {}
        Event(const v8::FunctionCallbackInfo<v8::Value>& info);

        void Execute();
    };

    class Camera;
    class GameObject;



    class JS_Vector3 {
    private:
        glm::vec3 vec;
    public:

        JS_Vector3(float x, float y, float z);

        JS_Vector3() {}

        operator glm::vec3& ();

        float GetX();

        float GetY() {
            return vec.y;
        }
        float GetZ() {
            return vec.z;
        }
        void SetX(float value) {
            vec.x = value;
        }
        void SetY(float value) {
            vec.y = value;
        }
        void SetZ(float value) {
            vec.z = value;
        }
        void plus(JS_Vector3 other) {
            this->vec += other.vec;
        }
        glm::vec3 GetNativeVector() {
            return vec;
        }

    };
    class JS_Transform {
    private:
       // friend class Transform;
        Transform* transform;
    public:
        JS_Transform(JS_Transform* transform) {
            this->transform = transform->transform;
        }
        void Move(JS_Vector3 position) {
            this->transform->SetPosition(position.GetNativeVector());
        }
    };
    class JS_GameObject {
    private:

        std::shared_ptr<GameObject> obj;
    public:

        JS_GameObject(JS_Vector3 vec, bool isParentScript = false);

        void SetObject(std::shared_ptr<GameObject> object);

        void Destroy();

        v8::Local<v8::Value> GetComponent(const v8::FunctionCallbackInfo<v8::Value>& info);

        ~JS_GameObject();
    };
    struct CameraWrapper
    {
    private:
        Camera* camera;
    public:

        CameraWrapper();

        void Update();

        ~CameraWrapper() {}
    };
}
*/