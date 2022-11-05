export module Camera_impl;
import Camera;
import BEbraMath;
import Input;

namespace BEbraEngine {

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 1.f;
    const float ZOOM = 45.0f;

    SimpleCamera::~SimpleCamera()
    {
        this->cameraData->buffer->destroy();
    }
    SimpleCamera::SimpleCamera(const Vector2& size, const Vector3& position, Vector3 up, float yaw, float pitch)
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
    Matrix4 SimpleCamera::getViewMatrix()
    {
        return BEbraMath::lookAt(Position, Position + Front, Up);
    }

    void SimpleCamera::lookAt(const Vector3& at)
    {
        Front = BEbraMath::normalize(at - Position);
    }

    bool SimpleCamera::isMain()
    {
        return _isMain;
    }

    void SimpleCamera::setMain(bool value)
    {
        _isMain = value;
    }

    void SimpleCamera::updateCameraVectors()
    {
        Vector3 front;
        front.x = cos(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
        front.y = sin(BEbraMath::radians(Pitch));
        front.z = sin(BEbraMath::radians(Yaw)) * cos(BEbraMath::radians(Pitch));
        Front = BEbraMath::normalize(front);
        Right = BEbraMath::normalize(BEbraMath::cross(Front, WorldUp));
        Up = BEbraMath::normalize(BEbraMath::cross(Right, Front));
    }

    void SimpleCamera::resize(Vector2 newSize)
    {
        rectViewport = newSize;
    }

    void SimpleCamera::update()
    {

        ShaderData vp;
        vp.proj = BEbraMath::perspective(BEbraMath::radians(45.0f), rectViewport.x / rectViewport.y, .1f, 10000.0f);
        vp.view = getViewMatrix();
        vp.position = Position;
        processMouseMovement();
        cameraData->setData(&vp, sizeof(ShaderData));
    }
    void SimpleCamera::processMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

    void SimpleCamera::processMouseMovement()
    {
        float xoffset;
        float yoffset;
        _move(xoffset, yoffset);

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        updateCameraVectors();
    }

    void SimpleCamera::_move(float& x, float& y)
    {

        x = Input::getX() - lastX;
        y = lastY - Input::getY();
        lastX = Input::getX();
        lastY = Input::getY();

    }

    void SimpleCamera::moveTo(const Vector3& newPos)
    {
        Position = newPos;
    }

    void SimpleCamera::processKeyboard(Camera_Movement direction, float deltaTime)
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

}