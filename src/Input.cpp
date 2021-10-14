#include "Input.hpp"


Input* Input::inst;

int* Input::mouse_x;

const uint8_t* Input::state;

int* Input::mouse_y;

int* Input::scroll_x;

int* Input::scroll_y;

Input::Input()
{
    mouse_x = new int();
    mouse_y = new int();
    scroll_x = new int();
    scroll_y = new int();
}
Input::~Input() {
    delete mouse_x;
    delete mouse_y;
    delete scroll_x;
    delete scroll_y;
}


void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    *inst->mouse_x = xpos;
    *inst->mouse_y = ypos;
}
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    *inst->scroll_x = xoffset;
    *inst->scroll_y = yoffset;
}


void Input::SetKeyBoardState(const Uint8* state)
{
    Input::getInstance()->state = state;
}

int Input::GetScrollX()
{
    return *inst->scroll_x;
}

int Input::GetScrollY()
{
    return *inst->scroll_y;
}

int Input::GetX()
{
    return *inst->mouse_x;
}

int Input::GetY()
{
    return *inst->mouse_y;
}

void Input::SetWindow(SDL_Window* window)
{
    SDL_GetMouseState(Input::mouse_x, Input::mouse_y);
    Input::getInstance()->window = window;
}
void Input::SetWindow(GLFWwindow* window)
{
    Input::getInstance()->window1 = window;
    glfwSetCursorPosCallback(window, mouse_callback);
}

Input* Input::getInstance()
{
    if (!inst)
        inst = new Input();
    return inst;
}

bool Input::IsKeyPressed(SDL_Scancode key)
{
   // if (Input::state[key])
    //    return true;
    return false;
}
