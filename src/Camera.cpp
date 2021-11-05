
#pragma once
#include "stdafx.h"
#define NOMINMAX
#include "Camera.hpp"
#include "Input.hpp"
#include "BaseVulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "RenderBuffer.hpp"
namespace BEbraEngine {

    Camera::Camera(Vector3 position , Vector3 up , float yaw, float pitch)
        : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Front = Vector3(0, 0, -1);
        Pitch = pitch;
        lastX = Input::GetX();
        lastY = Input::GetY();
        updateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = Vector3(posX, posY, posZ);
        WorldUp = Vector3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        glm::vec3 _pos = Position;
        glm::vec3 pos_f = Position + Front;
        glm::vec3 up = Up;
        return glm::lookAt(_pos, pos_f, up);
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
        x = Input::GetX() - lastX;
        y = lastY - Input::GetY(); // �����������, ��� ��� y-���������� ���� ����� �����
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

        // ����������, ��� ����� ������ ������� �� ������� ������, ����� �� ����������������
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // ��������� �������� �������-�����, �������-������ � �������-�����, ��������� ����������� �������� ����� ������
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


    void Camera::Update()
    {

        ShaderData vp;
        vp.proj = glm::perspective(glm::radians(45.0f), WIDTH / (float)HEIGHT, 0.0001f, 10000.0f);
        vp.view = GetViewMatrix();
        vp.position = static_cast<glm::vec3>(Position);
        ProcessMouseMovement();
        cameraData->setData(&vp, sizeof(ShaderData));
    }

    void Camera::updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(static_cast<glm::vec3>(Front), 
                                          static_cast<glm::vec3>(WorldUp)));  

        // 
        Up = glm::normalize(glm::cross(static_cast<glm::vec3>(Right), 
                                       static_cast<glm::vec3>(Front)));
    }
}