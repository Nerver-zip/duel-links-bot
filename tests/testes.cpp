#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

// Resolução original de captura (Full HD)
const int ORIGINAL_WIDTH = 1920;
const int ORIGINAL_HEIGHT = 1080;

// Captura a tela com escala
Mat capturaTela(float scale) {
    HWND hwnd = GetDesktopWindow();
    HDC hwindowDC = GetDC(hwnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    int adjustedWidth = static_cast<int>(width * scale);
    int adjustedHeight = static_cast<int>(height * scale);

    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, adjustedWidth, adjustedHeight);
    SelectObject(hwindowCompatibleDC, hbwindow);

    BitBlt(hwindowCompatibleDC, 0, 0, adjustedWidth, adjustedHeight, hwindowDC, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = adjustedWidth;
    bi.biHeight = -adjustedHeight;
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

// Função para redimensionar o template baseado na resolução do jogo
Mat redimensionarTemplateParaResolucao(const string& caminho, int larguraDest, int alturaDest) {
    Mat original = imread(caminho);
    if (original.empty()) {
        cerr << "Erro ao carregar o template." << endl;
        return Mat();
    }

    // Escala proporcional baseada na resolução original do botão (1920x1080)
    float escalaX = static_cast<float>(larguraDest) / ORIGINAL_WIDTH;
    float escalaY = static_cast<float>(alturaDest) / ORIGINAL_HEIGHT;
    float escala = min(escalaX, escalaY);  // Mantém proporção

    // Redimensiona com escala proporcional
    Mat redimensionado;
    resize(original, redimensionado, Size(), escala, escala, INTER_LINEAR);

    // Exibe o botão para debug
    imshow("Botao Redimensionado", redimensionado);
    waitKey(1);

    return redimensionado;
}

// Simula clique do mouse ajustado pela escala
void clicar(int x, int y, float scale) {
    x = static_cast<int>(x / scale);
    y = static_cast<int>(y / scale);

    SetCursorPos(x, y);
    Sleep(1000);

    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    INPUT inputs[2] = {inputDown, inputUp};
    SendInput(2, inputs, sizeof(INPUT));
}

int main() {
    std::cout << "TESTE!" << "\n";
    this_thread::sleep_for(chrono::seconds(3));

    // Defina a resolução de destino do jogo (exemplo: 800x450)
    int larguraDest = 1920;
    int alturaDest = 1080;

    // Redimensiona o botão com base na resolução de destino
    Mat botao = redimensionarTemplateParaResolucao("C:/Users/marce/Desktop/duelLinks-auto-gate-farm/assets/duel_log.png", larguraDest, alturaDest);
    if (botao.empty()) {
        return -1;
    }

    float scale = 1.25; // Ajuste de escala para captura de tela e clique

    while (true) {
        Mat tela = capturaTela(scale);

        Mat resultado;
        matchTemplate(tela, botao, resultado, TM_CCOEFF_NORMED);

        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(resultado, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal >= 0.9) {
            int x = maxLoc.x + botao.cols / 2;
            int y = maxLoc.y + botao.rows / 2;
            cout << "Botao encontrado em: " << x << ", " << y << endl;
            clicar(x, y, scale);
        } else {
            cout << "Botao NAO encontrado! " << "Correspondencia: " << maxVal << "\n";
        }

        this_thread::sleep_for(chrono::seconds(3));
    }

    return 0;
}
