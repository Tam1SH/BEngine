#pragma once
#include "stdafx.h"
#include "platform_window.hpp"

namespace BEbraEngine {
    
    enum class KEY_CODE {
        
        KEY_0 = SDL_SCANCODE_0,
        KEY_1 = SDL_SCANCODE_1,
        KEY_2 = SDL_SCANCODE_2,
        KEY_3 = SDL_SCANCODE_3,
        KEY_4 = SDL_SCANCODE_4,
        KEY_5 = SDL_SCANCODE_5,
        KEY_6 = SDL_SCANCODE_6,
        KEY_7 = SDL_SCANCODE_7,
        KEY_8 = SDL_SCANCODE_8,
        KEY_9 = SDL_SCANCODE_9,

        KEY_MINUS = SDL_SCANCODE_MINUS,
        KEY_EQUAL = SDL_SCANCODE_EQUALS,
        KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        KEY_Q = SDL_SCANCODE_Q,
        KEY_W = SDL_SCANCODE_W,
        KEY_E = SDL_SCANCODE_E,
        KEY_R = SDL_SCANCODE_R,
        KEY_T = SDL_SCANCODE_T,
        KEY_Y = SDL_SCANCODE_Y,
        KEY_U = SDL_SCANCODE_U,
        KEY_I = SDL_SCANCODE_I,
        KEY_O = SDL_SCANCODE_O,
        KEY_P = SDL_SCANCODE_P,
        KEY_LEFT_BRACKET = SDL_SCANCODE_LEFTBRACKET,
        KEY_RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,
        KEY_A = SDL_SCANCODE_A,
        KEY_S = SDL_SCANCODE_S,
        KEY_D = SDL_SCANCODE_D,
        KEY_F = SDL_SCANCODE_F,
        KEY_G = SDL_SCANCODE_G,
        KEY_H = SDL_SCANCODE_H,
        KEY_J = SDL_SCANCODE_J,
        KEY_K = SDL_SCANCODE_K,
        KEY_L = SDL_SCANCODE_L,
        KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
        KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
        KEY_Z = SDL_SCANCODE_Z,
        KEY_X = SDL_SCANCODE_X,
        KEY_C = SDL_SCANCODE_C,
        KEY_V = SDL_SCANCODE_V,
        KEY_B = SDL_SCANCODE_B,
        KEY_N = SDL_SCANCODE_N,
        KEY_M = SDL_SCANCODE_M,
        KEY_COMMA = SDL_SCANCODE_COMMA,
        KEY_PERIOD = SDL_SCANCODE_PERIOD,
        KEY_SLASH = SDL_SCANCODE_SLASH,
        KEY_CAPS_LOCK = SDL_SCANCODE_CAPSLOCK,
        KEY_TAB = SDL_SCANCODE_TAB,
        KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
        KEY_ENTER = SDL_SCANCODE_KP_ENTER,
        KEY_LEFT_CONTROL = SDL_SCANCODE_LCTRL,
        KEY_RIGHT_CONTROL = SDL_SCANCODE_RCTRL,
        KEY_LEFT_ALT = SDL_SCANCODE_LALT,
        KEY_RIGHT_ALT = SDL_SCANCODE_RALT,
        KEY_RIGHT_F1 = SDL_SCANCODE_F1,
        KEY_RIGHT_F2 = SDL_SCANCODE_F2,
        KEY_RIGHT_F3 = SDL_SCANCODE_F3,
        KEY_RIGHT_F4 = SDL_SCANCODE_F4,
        KEY_RIGHT_F5 = SDL_SCANCODE_F5,
        KEY_RIGHT_F6 = SDL_SCANCODE_F6,
        KEY_RIGHT_F7 = SDL_SCANCODE_F7,
        KEY_RIGHT_F8 = SDL_SCANCODE_F8,
        KEY_RIGHT_F9 = SDL_SCANCODE_F9,
        KEY_RIGHT_F10 = SDL_SCANCODE_F10,
        KEY_RIGHT_F11 = SDL_SCANCODE_F11,
        KEY_RIGHT_F12 = SDL_SCANCODE_F12,
        KEY_SPACE = SDL_SCANCODE_SPACE,
        KEY_RIGHT_SHIFT = SDL_SCANCODE_RSHIFT
    };
    

    class Input {
        struct InputState {
            float x{}, y{};
            float scrollX{}, scrollY{};

        };
    public:
        friend class BaseWindow;

        static void setKeyBoardState(const Uint8* state);

        static float getScrollX();

        static float getScrollY();

        static float getX();

        static float getY();

        static float getOffsetX();

        static float getOffsetY();

        static void setWindow(WindowHandle* window);

        static bool isKeyPressed(KEY_CODE key);

        static bool isKeyReleased(KEY_CODE key);

        Input();

        ~Input();
    private:

        static void update(InputState& state);

        static float* mouseX;

        static float* mouseY;

        static float* lastX;
        
        static float* lastY;

        static const Uint8* state;

        static const Uint8* oldState;

        static float* scrollX;

        static float* scrollY;

        static WindowHandle* window;

    };
}
