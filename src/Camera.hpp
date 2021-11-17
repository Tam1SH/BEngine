
#ifndef CAMERA_H
#define CAMERA_H

#include "AbstractComponent.hpp"
#include "matrix.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {
    class RenderBufferView;

}
//TODO: ну, почти.
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

   
    class Camera : public GameObjectComponent
    {
    public:
        RenderBufferView* cameraData;
        
        Vector3 Position;
        Vector3 Front;
        Vector3 Up;
        Vector3 Right;
        Vector3 WorldUp;

        Camera() {}
        ~Camera();
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
    private:
        struct ShaderData {
            Matrix4 proj;
            Matrix4 view;
            alignas(16) Vector3 position;

        };


        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        float lastX;
        float lastY;
    };
}
#endif
