module;
#include <boost/filesystem.hpp>

export module Camera;
import Vector2;
import Matrix4;
import Vector3;
import RenderBuffer;
import GameComponent;

namespace BEbraEngine {

    export enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };




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

        ~SimpleCamera();


        SimpleCamera(const Vector2& size, const Vector3& position, Vector3 up = Vector3(0, 1, 0), float yaw = 0, float pitch = 0);

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            //destroyer.destroyLight(*this);
        }

        Matrix4 getViewMatrix();

        void moveTo(const Vector3& newPos);

        void processKeyboard(Camera_Movement direction, float deltaTime);

        void _move(float& x, float& y);

        void processMouseMovement();

        void processMouseScroll(float yoffset);

        void update();

        void resize(Vector2 newSize);

        void lookAt(const Vector3& at);

        bool isMain();

        void setMain(bool value);


    private:
        void updateCameraVectors();
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
