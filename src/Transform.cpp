#include "stdafx.h"
#define NOMINMAX
#include "Transform.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "TransformFactory.hpp"
#include "btBulletDynamicsCommon.h"
#include "BaseVulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    TransformFactory* Transform::factory;

    void Transform::SetFactory(TransformFactory* factory) noexcept 
    {
        Transform::factory = factory;
    }

    Transform* Transform::New(const Vector3& position)
    {
        return factory->Create(position);
    }

    Transform::Transform(const Vector3& position)
    {
        std::cout << "TRANSFORM " << this << " CREATED" << std::endl;
        this->position = position;
        scale = Vector3(1);
        rotation = Vector3(1);
        model = glm::mat4(1);
    }

    void Transform::UpdatePosition(const Vector3& position)
    {
        this->position = position;

        model = glm::mat4(1);
        glm::mat4 _m = model;
        glm::vec3 _s = scale;
        glm::vec3 _p = position;
        model = glm::translate(_m, _p);
        glm::mat4 _m1 = model;
        model = glm::scale(_m1, _s);
        buffer->setData(&model, sizeof(Matrix4));
    }

    void Transform::SetPosition(const Vector3& position) noexcept
    {
        this->position = position;
    }


    void Transform::SetScale(const Vector3& scale) noexcept
    {
        this->scale = scale;
    }

    Vector3 Transform::GetPosition() const noexcept
    {
        return position;
    }
}
