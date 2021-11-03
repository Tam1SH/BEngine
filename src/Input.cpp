#include "stdafx.h"
#include "Input.hpp"
#include <iostream>
namespace BEbraEngine {

    int* Input::mouse_x = new int();

    const uint8_t* Input::state;

    int* Input::mouse_y = new int();

    int* Input::scroll_x = new int();

    int* Input::scroll_y = new int();

    SDL_Window* Input::window;

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
    bool Input::IsKeyPressed(KEY_CODE key)
    {
        if (Input::state[(int)key])
            return true;
        return false;
    }

    void Input::SetWindow(WindowHandle* window)
    {
        
        SDL_GetMouseState(Input::mouse_x, Input::mouse_y);
        Input::state = SDL_GetKeyboardState(NULL);
        Input::window = window;
    }

}
