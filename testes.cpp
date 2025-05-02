#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

// Captura a tela inteira do desktop como Mat do OpenCV
Mat capturaTela(float scale) {
    HWND hwnd = GetDesktopWindow();
    HDC hwindowDC = GetDC(hwnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);

    int width = GetSystemMetrics(SM_CXSCREEN);  // Largura da tela
    int height = GetSystemMetrics(SM_CYSCREEN); // Altura da tela

    // Escala de 125%, ajustando a resolução real
    float scale = 1.25;
    int adjustedWidth = static_cast<int>(width * scale);  // Ajusta a largura
    int adjustedHeight = static_cast<int>(height * scale); // Ajusta a altura

    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, adjustedWidth, adjustedHeight);
    SelectObject(hwindowCompatibleDC, hbwindow);

    BitBlt(hwindowCompatibleDC, 0, 0, adjustedWidth, adjustedHeight, hwindowDC, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = adjustedWidth;
    bi.biHeight = -adjustedHeight; // negativo = origem no topo
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;

    Mat src(adjustedHeight, adjustedWidth, CV_8UC3);
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, adjustedHeight, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

// Simula clique do mouse em (x, y) com a compensação para a scale
void clicar(int x, int y, float scale) {
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

int main() {
    std::cout << "TESTE!" << "\n";
    this_thread::sleep_for(chrono::seconds(3));

    Mat botao = imread("C:/Users/marce/Desktop/duelLinks-auto-gate-farm/button.png");
    if (botao.empty()) {
        cout << "Erro ao carregar button.png" << endl;
        return -1;
    }

    float scale = 1.25; // Escala de 125%

    while (true) {
        Mat tela = capturaTela(scale);

        // Exibe a tela capturada, redimensionada para uma visualização mais adequada
        Mat telaRedimensionada;
        resize(tela, telaRedimensionada, Size(tela.cols / 2, tela.rows / 2)); // Reduz pela metade

        Mat resultado;
        matchTemplate(tela, botao, resultado, TM_CCOEFF_NORMED);

        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(resultado, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal >= 0.9) { // Ajuste a sensibilidade aqui
            // Encontra a posição do botão com base na imagem original
            int x = maxLoc.x + botao.cols / 2;
            int y = maxLoc.y + botao.rows / 2;
            cout << "Botao encontrado em: " << x << ", " << y << endl;
            clicar(x, y, scale);  // Passa a escala para compensar o clique
        } else {
            cout << "Botao NAO encontrado" << endl;
            return 0;
        }
        this_thread::sleep_for(chrono::seconds(3));
    }
    return 0;
}
