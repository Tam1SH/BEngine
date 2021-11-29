#pragma once
#include "IProxyGameObjectFactory.hpp"
namespace std {
    template<class Xyu, class Pizda>
    class unique_ptr;
}
namespace BEbraEngine {

}
namespace BEbraEngine {

    class ScriptObjectFactory : public IProxyGameObjectFactory {
    public:
        IProxyGameObjectFactory* realFactory;

        std::shared_ptr<GameObject> create(const Vector3& position) override;

        std::shared_ptr<PointLight> createLight(const Vector3& position) override;

        std::shared_ptr<DirectionLight> createDirLight(const Vector3& direction) override;

        void destroyObject(GameObject* object) override;

        void destroyObject(std::shared_ptr<GameObject> object) override;

        void destroyPointLight(std::shared_ptr<PointLight> light) override;

        std::shared_ptr<Camera> createCamera(const Vector3& position) override;

        void destroyCamera(std::shared_ptr<Camera> camera) override;

    };
}
