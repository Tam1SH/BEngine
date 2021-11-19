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
        std::unique_ptr<IProxyGameObjectFactory> realFactory;

        std::shared_ptr<GameObject> create(const Vector3& position) override;

        std::shared_ptr<PointLight> createLight(const Vector3& position) override;

        std::shared_ptr<DirectionLight> createDirLight(const Vector3& direction) override;

    };
}
