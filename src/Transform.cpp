#include "stdafx.h"
#define NOMINMAX
#include "IVisitorGameComponentDestroyer.hpp"
#include "Transform.hpp"
#include "TransformFactory.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Math.hpp"
namespace BEbraEngine {


    Matrix4 Transform::getBasis() const noexcept
    {

        auto model = Matrix4(1);

        model = BEbraMath::translate(model, position);
        model = BEbraMath::scale(model, scale);

        model *= BEbraMath::toMat4(quat);

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

    void Transform::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyTransformComponent(*this);
    }

    void Transform::updatePosition(const Vector3& position) noexcept
    {
        this->position = position;

    }

    void Transform::setPosition(const Vector3& position) noexcept
    {
        this->position = position;
    }


    void Transform::setScale(const Vector3& scale) noexcept
    {
        this->scale = scale;
    }

    void Transform::setQuat(const Quaternion& quat) noexcept
    {
        this->quat = quat;
    }

    Vector3& Transform::getPosition() noexcept
    {
        return position;
    }
    const Vector3& Transform::getPosition() const noexcept
    {
        return position;
    }
    Quaternion Transform::getRotation() const noexcept
    {
        return quat;
    }
}
