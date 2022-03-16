#include "stdafx.h"
#include "TransformFactory.hpp"
#include "Transform.hpp"
namespace BEbraEngine {
    std::optional<Transform*> TransformFactory::create(const Transform::CreateInfo& info)
    {
        auto trans = new Transform(info.position);
        trans->setScale(info.scale);
        trans->setName("Transform");
        return std::optional<Transform*>(trans);
    }

    TransformFactory::TransformFactory()
    {
    }
}