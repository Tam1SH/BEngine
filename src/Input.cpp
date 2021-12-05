#include "stdafx.h"
#include "Input.hpp"
#include <iostream>
namespace BEbraEngine {

    int* Input::mouse_x = new int();

    const uint8_t* Input::state;

    const uint8_t* Input::old_state;

    int* Input::mouse_y = new int();

    int* Input::scroll_x = new int();

    int* Input::scroll_y = new int();

    SDL_Window* Input::window;

    void Input::setKeyBoardState(const Uint8* state)
    {
        Input::state = state;
    }

    int Input::getScrollX()
    {
        return *Input::scroll_x;
    }

    int Input::getScrollY()
    {
        return *Input::scroll_y;
    }

    int Input::getX()
    {
        return *Input::mouse_x;
    }

    int Input::getY()
    {
        return *Input::mouse_y;
    }

    bool Input::isKeyPressed(KEY_CODE key)
    {
        if (Input::state[(int)key])
            return true;
        return false;
    }

    bool Input::isKeyReleased(KEY_CODE key)
    {
        if (Input::state[(int)key])
            return true;
        return false;
    }

    void Input::setWindow(WindowHandle* window)
    {
        
        SDL_GetMouseState(Input::mouse_x, Input::mouse_y);
        Input::state = SDL_GetKeyboardState(NULL);
        Input::old_state = SDL_GetKeyboardState(NULL);
        Input::window = window;
    }

}
