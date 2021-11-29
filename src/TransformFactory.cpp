#include "stdafx.h"
#include "TransformFactory.hpp"
#include "Transform.hpp"
namespace BEbraEngine {
    Transform* TransformFactory::create(const glm::vec3& position)
    {
        auto trans = new Transform(position);
        trans->setName("Transform");
        return trans;
    }

    TransformFactory::TransformFactory()
    {
    }
}