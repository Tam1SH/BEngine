#pragma once
#include <SDL.h>
#include <glfw3.h>
#include "platform_window.hpp"
class Input {
private:
    static Input* inst;

    static const Uint8* state;

    static int* scroll_x;

    static int* scroll_y;

    SDL_Window* window;

    GLFWwindow* window1;

    Input(const Input&);

    Input& operator=(Input&);

private:

    Input();
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:

    static int* mouse_x;

    static int* mouse_y;

    static void SetKeyBoardState(const Uint8* state);

    static int GetScrollX();

    static int GetScrollY();

    static int GetX();

    static int GetY();

    static void SetWindow(SDL_Window* window);

    static void SetWindow(GLFWwindow* window);

    static Input* getInstance();

    static bool IsKeyPressed(SDL_Scancode key);

    ~Input();

};

