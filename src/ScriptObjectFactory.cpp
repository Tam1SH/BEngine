#include "stdafx.h"
#include "ScriptObjectFactory.hpp"
#include "GameObject.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {

    std::shared_ptr<GameObject> ScriptObjectFactory::create(const Vector3& position)
    {
        return realFactory->create(position);
    }

    std::shared_ptr<PointLight> ScriptObjectFactory::createLight(const Vector3& position)
    {
        return realFactory->createLight(position);
    }

    std::shared_ptr<DirectionLight> ScriptObjectFactory::createDirLight(const Vector3& direction)
    {
        return realFactory->createDirLight(direction);
    }

    void ScriptObjectFactory::destroyObject(GameObject* object)
    {
        realFactory->destroyObject(object);
    }

    void ScriptObjectFactory::destroyObject(std::shared_ptr<GameObject> object)
    {
        realFactory->destroyObject(object);
    }

    void ScriptObjectFactory::destroyPointLight(std::shared_ptr<PointLight> light)
    {
        realFactory->destroyPointLight(light);
    }

    std::shared_ptr<Camera> ScriptObjectFactory::createCamera(const Vector3& position)
    {
        return realFactory->createCamera(position);
    }

    void ScriptObjectFactory::destroyCamera(std::shared_ptr<Camera> camera)
    {
        realFactory->destroyCamera(camera);
    }

}