#pragma once
#include "stdafx.h"
#include "platform_window.hpp"

namespace BEbraEngine {
    /*
    enum class KEY_CODE {
        KEY_0 = GLFW_KEY_0,
        KEY_1 = GLFW_KEY_1,
        KEY_2 = GLFW_KEY_2,
        KEY_3 = GLFW_KEY_3,
        KEY_4 = GLFW_KEY_5,
        KEY_6 = GLFW_KEY_6,
        KEY_7 = GLFW_KEY_7,
        KEY_8 = GLFW_KEY_8,
        KEY_9 = GLFW_KEY_9,
        KEY_MINUS = GLFW_KEY_MINUS,
        KEY_EQUAL = GLFW_KEY_EQUAL,
        KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
        KEY_Q = GLFW_KEY_Q,
        KEY_W = GLFW_KEY_W,
        KEY_E = GLFW_KEY_E,
        KEY_R = GLFW_KEY_R,
        KEY_T = GLFW_KEY_T,
        KEY_Y = GLFW_KEY_Y,
        KEY_U = GLFW_KEY_U,
        KEY_I = GLFW_KEY_I,
        KEY_O = GLFW_KEY_O,
        KEY_P = GLFW_KEY_P,
        KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
        KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
        KEY_A = GLFW_KEY_A,
        KEY_S = GLFW_KEY_S,
        KEY_D = GLFW_KEY_D,
        KEY_F = GLFW_KEY_F,
        KEY_G = GLFW_KEY_G,
        KEY_H = GLFW_KEY_H,
        KEY_J = GLFW_KEY_J,
        KEY_K = GLFW_KEY_K,
        KEY_L = GLFW_KEY_L,
        KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
        KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
        KEY_Z = GLFW_KEY_Z,
        KEY_X = GLFW_KEY_X,
        KEY_C = GLFW_KEY_C,
        KEY_V = GLFW_KEY_V,
        KEY_B = GLFW_KEY_B,
        KEY_N = GLFW_KEY_N,
        KEY_M = GLFW_KEY_M,
        KEY_COMMA = GLFW_KEY_COMMA,
        KEY_PERIOD = GLFW_KEY_PERIOD,
        KEY_SLASH = GLFW_KEY_SLASH,
        KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        KEY_TAB = GLFW_KEY_TAB,
        KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        KEY_ENTER = GLFW_KEY_ENTER,
        KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
        KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        KEY_RIGHT_F1 = GLFW_KEY_F1,
        KEY_RIGHT_F2 = GLFW_KEY_F2,
        KEY_RIGHT_F3 = GLFW_KEY_F3,
        KEY_RIGHT_F4 = GLFW_KEY_F4,
        KEY_RIGHT_F5 = GLFW_KEY_F5,
        KEY_RIGHT_F6 = GLFW_KEY_F6,
        KEY_RIGHT_F7 = GLFW_KEY_F7,
        KEY_RIGHT_F8 = GLFW_KEY_F8,
        KEY_RIGHT_F9 = GLFW_KEY_F9,
        KEY_RIGHT_F10 = GLFW_KEY_F10,
        KEY_RIGHT_F11 = GLFW_KEY_F11,
        KEY_RIGHT_F12 = GLFW_KEY_F12,
        KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
        KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
        KEY_SPACE = GLFW_KEY_SPACE,
        KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT
    };
    */
    class Input {

    private:

       // static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

       // static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        //static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:

        static int* mouse_x;

        static int* mouse_y;

        static void SetKeyBoardState(const Uint8* state);

        static int GetScrollX();

        static int GetScrollY();

        static int GetX();

        static int GetY();

        static void SetWindow(SDL_Window* window);

        //static void SetWindow(GLFWwindow* window);

        static bool IsKeyPressed(SDL_Scancode key);

        //static bool IsKeyPressed(KEY_CODE key);

        Input();

        ~Input();
    private:

        static const Uint8* state;

        static int* scroll_x;

        static int* scroll_y;

        static WindowHandle* window;

        //static GLFWwindow* window1;
    };
}
