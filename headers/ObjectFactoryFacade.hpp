#pragma once
#include "stdafx.h"
#include "platform.hpp"

#include "Vector3.hpp"

using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::string;

BE_NAMESPACE_STD_BEGIN
    template<class Xyu, class Pizda>
    class unique_ptr;
    template<class T>
    class shared_ptr;
BE_NAMESPACE_STD_END

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

        void destroy(shared_ptr<GameObject>& object);

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
