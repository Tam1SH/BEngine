#pragma once
#include "AbstractComponent.hpp"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    class TransformFactory;
    class Transform : public AbstractComponent {
    private:
        friend class TransformFactory;

        friend class RenderObjectFactory;

        static TransformFactory* factory;

        std::shared_ptr<RenderBuffer> buffer;


    private:
        glm::vec3 position;

        glm::vec3 scale;

        glm::vec3 rotation;

        glm::mat4 model;
    private:

        static void SetFactory(TransformFactory* factory) noexcept;

        Transform(const glm::vec3& position);

    public:

        static Transform* New(const glm::vec3& position = glm::vec3(0));

        void UpdatePosition(const glm::vec3& position);

        void SetPosition(const glm::vec3& position) noexcept;

        void SetScale(const glm::vec3& scale) noexcept;

        glm::vec3 GetPosition() const noexcept;

        ~Transform() { };
    };
}