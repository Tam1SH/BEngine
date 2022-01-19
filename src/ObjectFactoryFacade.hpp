#pragma once
#include "stdafx.h"
#include "Vector3.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::string;

namespace std {
    template<class Xyu, class Pizda>
    class unique_ptr;
    template<class T>
    class shared_ptr;
}
namespace BEbraEngine {
    class GameObjectFactory;
    class ScriptState;
    class SimpleCamera;
    class GameObject;
    class PointLight;
    class DirectionLight;
}
namespace BEbraEngine {

    class ObjectFactoryFacade final {
    public:

        shared_ptr<GameObject> create(const Vector3& position);

        shared_ptr<PointLight> createLight(const Vector3& position);

        shared_ptr<DirectionLight> createDirLight(const Vector3& direction);

        void destroy(GameObject& object);

        void destroyPointLight(PointLight& light);

        shared_ptr<SimpleCamera> createCamera(const Vector3& position);

        void destroyCamera(SimpleCamera& camera);

        void setModel(GameObject& object, const string& path);

        void setContext(ScriptState* logic);

        ObjectFactoryFacade() {}

        ObjectFactoryFacade(GameObjectFactory* factory);


    private:
        GameObjectFactory* realFactory_{};
        ScriptState* state_{};
    };
}
