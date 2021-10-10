
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "AbstractComponent.hpp"
#include <vulkan/vulkan.h>
#include "VkBuffer.hpp"
namespace BEbraEngine {
    // ���������� ��������� ��������� ��������� �������� ������. ������������ � �������� ����������, ����� ��������� �������� �� ����������� ��� ������� ������� ������� �����
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };



    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    // ����������� ����� ������, ������� ������������ ������� ������ � ��������� ��������������� �������� ����, ������� � ������� ��� ������������� � OpenGL

    class BaseVulkanRender;
    class Camera : public AbstractComponent
    {
    private:
        static BaseVulkanRender* render;
    public:
        static Camera* instance;
        // ��������� ������ �� ���������

        static void SetRender(BaseVulkanRender* render);

        Buffer buffer;
        VkDescriptorSet set;

        float lastX;
        float lastY;
        // �������� ������
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // ���� ������
        float Yaw;
        float Pitch;
        // ��������� ������
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        int width;
        int height;
        // �����������, ������������ �������
        Camera() {}
        Camera(uint32_t width, uint32_t height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

        // �����������, ������������ �������
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


        // ���������� ������� ����, ����������� � �������������� ����� ������ � LookAt-������� 
        glm::mat4 GetViewMatrix();

        //������������ ������� ������, ���������� �� ����� ������������������ ������� �����. ��������� ������� �������� � ���� ������������� ������� ������������ (��� ��������������� ��� �� ������� ������)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        //������������ ������� ������, ���������� �� ������� ����� � ������� ����. ������� � �������� ���������� �������� �������� ��� � ����������� X, ��� � � ����������� Y.
        void _move(float& x, float& y);

        void ProcessMouseMovement(bool constrainPitch = true);

        // ������������ ������� ������, ���������� �� ������� ������ ��������� ����. ���������� ������ ������� ������ �� ������������ ��� �������� 
        void ProcessMouseScroll(float yoffset);

        void CreateCameraSet();

        void Update();

    private:
        // ��������� ������-����� �� (�����������) ����� ������ ������
        void updateCameraVectors();
    };
}
#endif
