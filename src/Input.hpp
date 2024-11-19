#pragma once

#include <SDL2/SDL.h>



class Input 
{
public:
    static Input* Instance();

public:
    bool IsXClicked();
    bool IsKeyPressed();

    char GetKeyUp();
    char GetKeyDown();

    bool IsLeftButtonClicked();
    bool IsRightButtonClicked();
    bool IsMiddleButtonClicked();
    
    int GetMousePositionX();
    int GetMousePositionY();

    int GetMouseMotionX();
    int GetMouseMotionY();

public:
    void Update();


private:
    Input();
    Input(const Input&);
    Input& operator=(Input&);

private:
    char m_keyUp;
    char m_keyDown;

    bool m_isXClicked;
    bool m_isKeyPressed;

    bool m_isLeftButtonClicked;
    bool m_isRightButtonClicked;
    bool m_isMiddleButtonClicked;

    int m_mouseMotionX;
    int m_mouseMotionY;

    int m_mousePositionX;
    int m_mousePositionY;
};