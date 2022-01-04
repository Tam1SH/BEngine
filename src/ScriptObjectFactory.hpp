#pragma once
#include "IProxyGameObjectFactory.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace std {
    template<class Xyu, class Pizda>
    class unique_ptr;
}
namespace BEbraEngine {
    class GameObjectFactory;
    class ScriptState;
}
namespace BEbraEngine {

    class ScriptObjectFactory : public IProxyGameObjectFactory {
    public:

        shared_ptr<GameObject> create(const Vector3& position);

        optional<shared_ptr<GameObject>> create(const GameObject::GameObjectCreateInfo& info) override;

        shared_ptr<PointLight> createLight(const Vector3& position) override;

        shared_ptr<DirectionLight> createDirLight(const Vector3& direction) override;

        void destroyObject(shared_ptr<GameObject> object) override;

        void destroyPointLight(shared_ptr<PointLight> light) override;

        shared_ptr<Camera> createCamera(const Vector3& position) override;

        void destroyCamera(std::shared_ptr<Camera> camera) override;

        void setModel(GameObject* object, const string& path) override;

        void setContext(ScriptState* logic);

        

        ScriptObjectFactory() {}

        ScriptObjectFactory(GameObjectFactory* factory);


    private:
        GameObjectFactory* realFactory_{};
        ScriptState* logic_{};
    };
}
