#include "Transform.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "TransformFactory.h"
#include "btBulletDynamicsCommon.h"
#include "BaseVulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace BEbraEngine {
    TransformFactory* Transform::factory;

    void Transform::SetFactory(TransformFactory* factory) noexcept 
    {
        Transform::factory = factory;
    }

    Transform* Transform::New(const glm::vec3& position)
    {
        return factory->Create(position);
    }

    Transform::Transform(const glm::vec3& position)
    {
        std::cout << "TRANSFORM " << this << " CREATED" << std::endl;
        this->position = position;
        scale = glm::vec3(1);
        rotation = glm::vec3(1);
        model = glm::mat4(1);
    }

    void Transform::UpdatePosition(const glm::vec3& position)
    {
        VkDeviceMemory& memory = buffer->memory;

        this->position = position;


        model = glm::mat4(1);
        model = glm::translate(model, this->position);
        model = glm::scale(model, scale);

        void* data;
        vkMapMemory(BaseVulkanRender::device, memory, 0, sizeof(glm::mat4), 0, &data);
        memcpy(data, &model, sizeof(glm::mat4));
        vkUnmapMemory(BaseVulkanRender::device, memory);
    }

    void Transform::SetPosition(const glm::vec3& position) noexcept
    {
        this->position = position;
    }


    void Transform::SetScale(const glm::vec3& scale) noexcept
    {
        this->scale = scale;
    }

    glm::vec3 Transform::GetPosition() const noexcept
    {
        return position;
    }
}
