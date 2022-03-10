#include "stdafx.h"
#include "Input.hpp"
#include <iostream>
namespace BEbraEngine {

    float* Input::mouseX = new float();

    float* Input::lastX = new float();

    float* Input::lastY = new float();

    const uint8_t* Input::state;

    const uint8_t* Input::oldState;

    float* Input::mouseY = new float();

    float* Input::scrollX = new float();

    float* Input::scrollY = new float();

    SDL_Window* Input::window;

    void Input::update(InputState& state)
    {
        *scrollX = state.scrollX;
        *scrollY = state.scrollY;
        
        *mouseX = state.x;
        *mouseY = state.y;
    }

    void Input::setKeyBoardState(const Uint8* state)
    {
        Input::state = state;
    }

    float Input::getScrollX()
    {
        return *Input::scrollX;
    }

    float Input::getScrollY()
    {
        return *Input::scrollY;
    }

    float Input::getX()
    {
        return *Input::mouseX;
    }

    float Input::getY()
    {
        return *Input::mouseY;
    }

    float Input::getOffsetX()
    {
        return *Input::mouseX;
    }

    float Input::getOffsetY()
    {
        return *Input::mouseY;
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
        Input::state = SDL_GetKeyboardState(NULL);
        Input::oldState = SDL_GetKeyboardState(NULL);
        Input::window = window;
    }

}
