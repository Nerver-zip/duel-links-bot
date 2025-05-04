#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include "GameScreen.h"
#include "MouseEvents.h"

MouseEvents::MouseEvents(float scale) : scale(scale) {}

void MouseEvents::leftClick(int x, int y) {
    // Ajusta as coordenadas para a resolução da tela real considerando a scale
    x = static_cast<int>(x / scale); // Corrige a posição do clique
    y = static_cast<int>(y / scale); // Corrige a posição do clique

    SetCursorPos(x, y);

    Sleep(1000);

    // Prepara estrutura para pressionar o botão esquerdo
    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Prepara estrutura para soltar o botão esquerdo
    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    // Envia os dois eventos: clique completo
    INPUT inputs[2] = { inputDown, inputUp };
    UINT sent = SendInput(2, inputs, sizeof(INPUT));
}

void MouseEvents::clickButton(const Component& button, float accuracy){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.findComponent(button, accuracy);
    if (result.found)
        leftClick(result.center.first, result.center.second);
}

