#pragma once
#include <SDL.h>
class Input {
private:
    static Input* inst;

    static const Uint8* state;

    static int* scroll_x;

    static int* scroll_y;

    SDL_Window* window;

    Input(const Input&);

    Input& operator=(Input&);

private:

    Input();
    static void mouse_callback(SDL_Window* window, int xpos, int ypos);

    static void scroll_callback(SDL_Window* window, int xoffset, int yoffset);

public:

    static int* mouse_x;

    static int* mouse_y;

    static void SetKeyBoardState(const Uint8* state);

    static int GetScrollX();

    static int GetScrollY();

    static int GetX();

    static int GetY();

    static void SetWindow(SDL_Window* window);

    static Input* getInstance();

    static bool IsKeyPressed(SDL_Scancode key);

    ~Input();

};

