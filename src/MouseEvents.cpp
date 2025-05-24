#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include "GameScreen.h"
#include "MouseEvents.h"

void MouseEvents::leftClick(int x, int y) {

    GameScreen& screen = GameScreen::getInstance();
    
    
    x = static_cast<int>(x / screen.getScale()); //off set zoom if any
    y = static_cast<int>(y / screen.getScale()); 

    SetCursorPos(x, y);

    Sleep(1000);

    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    INPUT inputs[2] = { inputDown, inputUp };
    UINT sent = SendInput(2, inputs, sizeof(INPUT));
}

void MouseEvents::rightClick(int x, int y){
    GameScreen& screen = GameScreen::getInstance();
    
    
    x = static_cast<int>(x / screen.getScale()); //off set zoom if any
    y = static_cast<int>(y / screen.getScale()); 

    SetCursorPos(x, y);

    Sleep(1000);

    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    INPUT inputs[2] = { inputDown, inputUp };
    UINT sent = SendInput(2, inputs, sizeof(INPUT));
}

void MouseEvents::clickButton(const Component& button, float accuracy){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(button, accuracy);
    if (result.found)
        leftClick(result.coordinates.first, result.coordinates.second);
}

void MouseEvents::drag(int x1, int y1, int x2, int y2) {
    GameScreen& screen = GameScreen::getInstance();

    x1 = static_cast<int>(x1 / screen.getScale());
    y1 = static_cast<int>(y1 / screen.getScale());
    x2 = static_cast<int>(x2 / screen.getScale());
    y2 = static_cast<int>(y2 / screen.getScale());

    SetCursorPos(x1, y1);
    Sleep(200);

    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &inputDown, sizeof(INPUT));
    Sleep(100);

    SetCursorPos(x2, y2);
    Sleep(300);

    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &inputUp, sizeof(INPUT));
}


