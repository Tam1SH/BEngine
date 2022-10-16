module;
#include <boost/filesystem.hpp>
export module Camera;
import Vector2;
import Matrix4;
import Vector3;
import BEbraMath;
import RenderBuffer;
import GameComponent;
import Input;
import GameComponentDestroyerDecl;

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

        //void destroy(ÑGameComponentDestroyer auto& destroyer) {
        //    destroyer.destroyCameraComponent(*this);
        //}

        void destroy(GameComponentDestroyer& destroyer) override;

        Matrix4 getViewMatrix();

        void moveTo(const Vector3& newPos);

        void processKeyboard(Camera_Movement direction, float deltaTime);

        void _move(float& x, float& y);

        void processMouseMovement();

        void processMouseScroll(float yoffset);

        void update();


        void resize(Vector2 newSize);

        void lookAt(const Vector3& at);

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
