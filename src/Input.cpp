#include "Input.hpp"
#include <iostream>
namespace BEbraEngine {

    int* Input::mouse_x = new int();

    const uint8_t* Input::state;

    int* Input::mouse_y = new int();

    int* Input::scroll_x = new int();

    int* Input::scroll_y = new int();

    GLFWwindow* Input::window1;

    SDL_Window* Input::window;


    void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        *Input::mouse_x = xpos;
        *Input::mouse_y = ypos;
    }
    void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        *Input::scroll_x = xoffset;
        *Input::scroll_y = yoffset;
    }


    void Input::SetKeyBoardState(const Uint8* state)
    {
        Input::state = state;
    }

    int Input::GetScrollX()
    {
        return *Input::scroll_x;
    }

    int Input::GetScrollY()
    {
        return *Input::scroll_y;
    }

    int Input::GetX()
    {
        return *Input::mouse_x;
    }

    int Input::GetY()
    {
        return *Input::mouse_y;
    }
    void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }

    void Input::SetWindow(SDL_Window* window)
    {
        SDL_GetMouseState(Input::mouse_x, Input::mouse_y);
        Input::state = SDL_GetKeyboardState(NULL);
        Input::window = window;
    }
    void Input::SetWindow(GLFWwindow* window)
    {
        Input::window1 = window;
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
        glfwSetKeyCallback(window, KeyCallback);

    }


    bool Input::IsKeyPressed(SDL_Scancode key)
    {
        if (Input::state[key])
            return true;
        return false;
    }
    bool Input::IsKeyPressed(KEY_CODE key)
    {
        
        if (glfwGetKey(window1, (int)key) == GLFW_PRESS)
             return true;
        return false;
    }
}
