#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


export module Camera;
import Vector2;
import Matrix4;
import Vector3;
import BEbraMath;
import RenderBuffer;
import GameComponent;
import Input;

//import ÑVisitorComponentDestroyer;
namespace BEbraEngine {
    class RenderBufferView;
    class IVisitorGameComponentDestroyer;
}

namespace BEbraEngine {
    export enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };



    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 1.f;
    const float ZOOM = 45.0f;


    export class SimpleCamera : public GameComponent
    {
    public:
        struct ShaderData {
            Matrix4 proj;
            Matrix4 view;
            alignas(16) Vector3 position;

        };
    public:
        RenderBufferView* cameraData{};

        Vector3 Position{};
        Vector3 Front{};
        Vector3 Up{};
        Vector3 Right{};
        Vector3 WorldUp{};

    public:

        SimpleCamera() {}

        ~SimpleCamera() {
            this->cameraData->buffer->destroy();
        }

        SimpleCamera(const Vector2& size, const Vector3& position, Vector3 up = Vector3(0,1,0), float yaw = 0, float pitch = 0)
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

        void destroy(IVisitorGameComponentDestroyer& destroyer) { } //override;

        //void destroy(ÑVisitorComponentDestroyer auto& destroyer) {
        //    destroyer.destroyCameraComponent(*this);
        //}

        Matrix4 getViewMatrix()
        {
            
            glm::vec3 _pos = Position;
            glm::vec3 pos_f = Position + Front;
            glm::vec3 up = Up;
            return glm::lookAt(_pos, pos_f, up);
        }

        void moveTo(const Vector3& newPos)
        {
            Position = newPos;
        }

        void processKeyboard(Camera_Movement direction, float deltaTime)
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


        void _move(float& x, float& y)
        {

            x = Input::getX() - lastX;
            y = lastY - Input::getY();
            lastX = Input::getX();
            lastY = Input::getY();

        }

        void processMouseMovement(bool constrainPitch = true)
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

        void processMouseScroll(float yoffset)
        {
            if (Zoom >= 1.0f && Zoom <= 45.0f)
                Zoom -= yoffset;
            if (Zoom <= 1.0f)
                Zoom = 1.0f;
            if (Zoom >= 45.0f)
                Zoom = 45.0f;
        }
        void update()
        {

            ShaderData vp;
            vp.proj = glm::perspective(glm::radians(45.0f), rectViewport.x / rectViewport.y, .1f, 10000.0f);
            vp.view = getViewMatrix();
            vp.position = Position;
            processMouseMovement();
            cameraData->setData(&vp, sizeof(ShaderData));
        }


        void resize(Vector2 newSize)
        {
            rectViewport = newSize;
        }

        void lookAt(const Vector3& at)
        {
             Front = BEbraMath::normalize(at - Position);
        }

        bool isMain() { return _isMain; }

        void setMain(bool value) { _isMain = value; }

    private:
        void updateCameraVectors()
        {
            Vector3 front;
            front.x = cos(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
            front.y = sin(BEbraMath::radians(Pitch));
            front.z = sin(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
            Front = BEbraMath::normalize(front);
            Right = BEbraMath::normalize(BEbraMath::cross(Front, WorldUp));  
            Up = BEbraMath::normalize(BEbraMath::cross(Right, Front));
        }
    private:

        float Yaw{};
        float Pitch{};

        float MovementSpeed{};
        float MouseSensitivity{};
        float Zoom{};

        int lastX{};
        int lastY{};

        int cursorX{};
        int cursorY{};
        bool _isMain{};
        Vector2 rectViewport{};




    };




}
