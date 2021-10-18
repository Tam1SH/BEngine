#pragma once
#define NOMINMAX
#include "Camera.hpp"
#include "Input.hpp"
#include "BaseVulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace BEbraEngine {
    Camera* Camera::instance;
    BaseVulkanRender* Camera::render;
    void Camera::SetRender(BaseVulkanRender* render)
    {
        Camera::render = render;
    }

    Camera::Camera(uint32_t width, uint32_t height, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), width(width), height(height)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
        instance = this;
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()

    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void Camera::_move(float& x, float& y)
    {

        static bool f = true;
        if (f) {
            lastX = Input::GetX();
            lastY = Input::GetY();
            f = false;
        }

        x = Input::GetX() - lastX;
        y = lastY - Input::GetY(); // перевернуто, так как y-координаты идут снизу вверх

        lastX = Input::GetX();
        lastY = Input::GetY();
    }

    void Camera::ProcessMouseMovement(bool constrainPitch)
    {
        float xoffset;
        float yoffset;
        _move(xoffset, yoffset);
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // Убеждаемся, что когда тангаж выходит за пределы обзора, экран не переворачивается
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Обновляем значения вектора-прямо, вектора-вправо и вектора-вверх, используя обновленные значения углов Эйлера
        updateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

    void Camera::CreateCameraSet()
    {

        VkDescriptorSetLayout layout = render->CameraLayout;
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = render->descriptorPool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &layout;
        if (VkResult result = vkAllocateDescriptorSets(render->GetDevice(), &allocInfo, &set); result != VK_SUCCESS) {
            throw std::runtime_error("ddd");
        }


        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer.self;
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(glm::mat4) * 2;

        std::array<VkWriteDescriptorSet, 1> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = set;
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(render->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void Camera::Update()
    {
        struct Pizda {
            alignas(16) glm::mat4 mat;
            alignas(16) glm::mat4 proj;

        };
        Pizda p;
        p.proj = glm::perspective(glm::radians(45.0f), WIDTH / (float)HEIGHT, 0.0001f, 10000.0f);
        p.proj[1][1] *= -1;
        p.mat = GetViewMatrix();
        ProcessMouseMovement();
        void* data;

        vkMapMemory(BaseVulkanRender::device, buffer.memory, 0, sizeof(glm::mat4) * 2, 0, &data);
        memcpy(data, &p, sizeof(glm::mat4) * 2);
        vkUnmapMemory(BaseVulkanRender::device, buffer.memory);
    }

    void Camera::updateCameraVectors()

    {
        // Вычисляем новый вектор-прямо
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Также пересчитываем вектор-вправо и вектор-вверх
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Нормализуем векторы, потому что их длина становится стремится к 0 тем больше, чем больше вы смотрите вверх или вниз, что приводит к более медленному движению.
        Up = glm::normalize(glm::cross(Right, Front));
    }
}