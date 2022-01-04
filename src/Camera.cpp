
#pragma once
#include "stdafx.h"
#define NOMINMAX
#include "Camera.hpp"
#include "Input.hpp"
#include "VulkanRender.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "RenderBuffer.hpp"
#include "Math.hpp"
namespace BEbraEngine {

    Camera::Camera(const Vector2& size, const Vector3& position , Vector3 up , float yaw, float pitch)
        : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        rectViewport = size;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Front = Vector3(0, 0, -1);
        Pitch = pitch;
        lastX = Input::getX();
        lastY = Input::getY();
        updateCameraVectors();
    }


    glm::mat4 Camera::getViewMatrix()
    {
        glm::vec3 _pos = Position;
        glm::vec3 pos_f = Position + Front;
        glm::vec3 up = Up;
        return glm::lookAt(_pos, pos_f, up);
    }

    void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
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
        
        x = Input::getOffsetX();
        y = Input::getOffsetY();
        

    }

    void Camera::processMouseMovement(bool constrainPitch)
    {
        float xoffset;
        float yoffset;
        _move(xoffset, yoffset);

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void Camera::processMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }


    void Camera::update()
    {

        ShaderData vp;
        vp.proj = glm::perspective(glm::radians(45.0f), rectViewport.x / rectViewport.y, .1f, 10000.0f);
        vp.view = getViewMatrix();
        vp.position = Position;
        processMouseMovement();
        cameraData->setData(&vp, sizeof(ShaderData));
    }

    void Camera::resize(Vector2 newSize)
    {
        rectViewport = newSize;
    }

    void Camera::lookAt(const Vector3& at)
    {
        Front = BEbraMath::normalize(at - Position);
    }



    void Camera::updateCameraVectors()
    {
        Vector3 front;
        front.x = cos(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
        front.y = sin(BEbraMath::radians(Pitch));
        front.z = sin(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
        Front = BEbraMath::normalize(front);
        Right = BEbraMath::normalize(BEbraMath::cross(Front, WorldUp));  
        Up = BEbraMath::normalize(BEbraMath::cross(Right, Front));
    }
    void Camera::release()
    {
    }
    Camera::~Camera() {
        this->cameraData->buffer->destroy();
    }
}