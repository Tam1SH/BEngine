
#ifndef CAMERA_H
#define CAMERA_H

#include "AbstractComponent.hpp"
#include "RenderBuffer.hpp"
#include "matrix.hpp"
#include "Vector3.h"
//TODO: нарушает и S и D в солиде блять. Избавиться нахуй от признаков того, что это вообще рендериться.
namespace BEbraEngine {
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

   
    class Camera : public AbstractComponent
    {
    private:
        struct VP {
            Matrix4 proj;
            Matrix4 view;


        };


        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        float lastX;
        float lastY;
    public:
        RenderBuffer* cameraData;
        
        Vector3 Position;
        Vector3 Front;
        Vector3 Up;
        Vector3 Right;
        Vector3 WorldUp;

        Camera() {}
        
        Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

        
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


        glm::mat4 GetViewMatrix();
        
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void _move(float& x, float& y);

        void ProcessMouseMovement(bool constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

        void Update();

    private:
        void updateCameraVectors();
    };
}
#endif
