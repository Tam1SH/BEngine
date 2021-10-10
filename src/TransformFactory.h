#pragma once
#include <glm/glm.hpp>
namespace BEbraEngine {
    class Transform;
    class TransformFactory {
    private:
        friend class Transform;
    public:
        Transform* Create(const glm::vec3& position);

        TransformFactory();
    };
}
