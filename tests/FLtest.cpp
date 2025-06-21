#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

// Define coordenadas do clique de teste
const int CLICK_X = 500;
const int CLICK_Y = 300;

// Função de clique simples com DPI awareness
void performClick(int x, int y) {
    std::cout << "SetCursorPos(" << x << ", " << y << ")\n";
    SetCursorPos(x, y);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, inputs, sizeof(INPUT));
    std::cout << "Click sent.\n";
}

// GUI mode com FLTK
void runGuiMode() {
    Fl_Window* win = new Fl_Window(300, 200, "Teste de Clique");

    Fl_Button* btn = new Fl_Button(100, 80, 100, 30, "Clicar!");
    btn->callback([](Fl_Widget*, void*) {
        std::cout << "Botão clicado - enviando clique...\n";
        performClick(CLICK_X, CLICK_Y);
    });

    win->end();
    win->show();
    Fl::run();
}

// CLI mode
void runCliMode() {
    std::cout << "Iniciando sem GUI. Clicando em " << CLICK_X << ", " << CLICK_Y << "...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));  // tempo para o usuário ver
    performClick(CLICK_X, CLICK_Y);
}

int main() {
    // Tenta aplicar DPI Awareness (requer Windows Vista+)
    SetProcessDPIAware();

    int choice;
    std::cout << "Escolha o modo:\n";
    std::cout << "1 - Sem GUI (console)\n";
    std::cout << "2 - Com GUI (FLTK)\n";
    std::cout << ">>> ";
    std::cin >> choice;

    if (choice == 2) {
        runGuiMode();
    } else {
        runCliMode();
    }

    return 0;
}