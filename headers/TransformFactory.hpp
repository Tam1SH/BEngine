#pragma once
#include "stdafx.h"
#include <glm/glm.hpp>
#include "Transform.hpp"
namespace BEbraEngine {
    class TransformFactory {
    public:
        std::optional<Transform*> create(const Transform::CreateInfo& info);

        TransformFactory();
    private:
        friend class Transform;
    };
}
