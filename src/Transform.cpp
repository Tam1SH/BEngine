#include "stdafx.h"
#define NOMINMAX
#include "IVisitorGameComponentDestroyer.hpp"
#include "Transform.hpp"
#include "TransformFactory.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
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
    }

    Transform::Transform(const Vector3& position)
    {
        this->position = position;
        scale = Vector3(1);
    }

    void Transform::destroy(IVisitorGameComponentDestroyer* destroyer)
    {
        destroyer->destroyTransformComponent(this);
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
