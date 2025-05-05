#define WIN32_LEAN_AND_MEAN 
#define NOMINMAX            

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

using namespace cv;
using namespace std;

// Função para capturar a tela
Mat captureScreenMat(HWND hwnd) {
    HDC hwindowDC, hwindowCompatibleDC;
    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER bi;

    hwnd = GetDesktopWindow(); // Captura da tela inteira
    
    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom;  
    width = windowsize.right;

    src.create(height, width, CV_8UC4);

    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // negativo para ficar do jeito certo
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SelectObject(hwindowCompatibleDC, hbwindow);
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, width, height, SRCCOPY); 
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

// Função para mover e clicar no mouse
void ClickAt(int x, int y) {
    SetCursorPos(x, y);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main() {
    // Carrega a imagem do botão (modelo)
    Mat templateImage = imread("ok_button.png"); // <- você precisa ter essa imagem salva
    if (templateImage.empty()) {
        cout << "Erro: não foi possível carregar a imagem do botão!" << endl;
        return -1;
    }

    cout << "Aguardando 3 segundos..." << endl;
    Sleep(3000);

    // Captura a tela
    Mat screen = captureScreenMat(GetDesktopWindow());
    
    // Onde salvar o resultado da comparação
    Mat result;
    matchTemplate(screen, templateImage, result, TM_CCOEFF_NORMED);

    // Encontra o melhor local (pico de correlação)
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    cout << "Precisão da correspondência: " << maxVal << endl;

    // Define um threshold para decidir se encontrou ou não
    if (maxVal >= 0.8) { // 80% de certeza
        cout << "Botão encontrado em: (" << maxLoc.x << ", " << maxLoc.y << ")" << endl;
        ClickAt(maxLoc.x + templateImage.cols / 2, maxLoc.y + templateImage.rows / 2);
    } else {
        cout << "Botão não encontrado!" << endl;
    }

    return 0;
}
