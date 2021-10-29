#include "stdafx.h"
#include "TransformFactory.hpp"
#include "Transform.hpp"
namespace BEbraEngine {
    Transform* TransformFactory::Create(const glm::vec3& position)
    {
        auto trans = new Transform(position);
        trans->name = "Transform";
        return trans;
    }

    TransformFactory::TransformFactory()
    {
        Transform::SetFactory(this);
    }
}