#pragma once
#include <glm/glm.hpp>
namespace BEbraEngine {
    class Transform;
    class TransformFactory {
    public:
        Transform* create(const glm::vec3& position);

        TransformFactory();
    private:
        friend class Transform;
    };
}
