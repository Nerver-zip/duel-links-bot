#include <windows.h>
#include <iostream>

int main() {
    std::cout << "O bot vai agir em 3 segundos..." << std::endl;
    Sleep(3000);

    // Move o mouse para (500, 500)
    SetCursorPos(500, 500);

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

    Sleep(2000);

    SetCursorPos(500, 700);

    Sleep(1000);

    sent = SendInput(2, inputs, sizeof(INPUT));

    if (sent != 2) {
        std::cerr << "Erro ao enviar eventos de mouse." << std::endl;
    } else {
        std::cout << "Mouse movido e clique realizado!" << std::endl;
    }

    return 0;
}