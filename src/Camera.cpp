module Camera;
//import GameComponentDestroyer;
namespace BEbraEngine {
    void SimpleCamera::destroy(GameComponentDestroyer& destroyer)
    {
        //destroyer.destroyCameraComponent(*this);
    }

    Matrix4 SimpleCamera::getViewMatrix()
    {
        return BEbraMath::lookAt(Position, Position + Front, Up);
    }

    void SimpleCamera::lookAt(const Vector3& at)
    {
        Front = BEbraMath::normalize(at - Position);
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