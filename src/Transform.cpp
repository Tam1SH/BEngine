#include "stdafx.h"
#define NOMINMAX
#include "Transform.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "TransformFactory.hpp"
#include "btBulletDynamicsCommon.h"
#include "VulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/quaternion.hpp>
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {


    Matrix4 Transform::getBasis() const noexcept
    {
        auto model = glm::mat4(1);
        glm::vec3 _s = scale;
        glm::vec3 _p = position;
        model = glm::translate(model, _p);
        model = glm::scale(model, _s);
        model *= glm::toMat4(quartion);

        return Matrix4(model);
    }

    Transform::~Transform()
    {
#ifdef _DEBUG
        Debug::log("Destroy", this, "", Debug::ObjectType::Transform, Debug::MessageType::Info);
#endif 
    }

    Transform::Transform(const Vector3& position)
    {
        this->position = position;
        scale = Vector3(1);
#ifdef _DEBUG
        Debug::log("Create", this, "", Debug::ObjectType::Transform, Debug::MessageType::Info);
#endif 
    }

    void Transform::updatePosition(const Vector3& position, const Vector4& quat)
    {
        this->position = position;

        quartion.x = quat.x;
        quartion.y = quat.y;
        quartion.z = quat.z;
        quartion.w = quat.w;

    }

    void Transform::setPosition(const Vector3& position) noexcept
    {
        this->position = position;
    }


    void Transform::setScale(const Vector3& scale) noexcept
    {
        this->scale = scale;
    }

    Vector3 Transform::getPosition() const noexcept
    {
        return position;
    }
}
