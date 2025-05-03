#include "GameScreen.h"

using namespace cv;

GameScreen::GameScreen(float scale) : scale(scale) {}

void GameScreen::screenshot() {
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
    
    this->src = src;
}

MatchResult GameScreen::findComponent(const std::string& path, float accuracy){
    Mat component = imread(path);
    if (component.empty()) {
        std::cout << "Erro ao localizar componente" << "\n";
        return MatchResult();
    }
    Mat result;
    matchTemplate(src, component, result, TM_CCOEFF_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    std::pair<int,int> coordinates;
    if (maxVal >= accuracy) {
        coordinates.first = maxLoc.x + component.cols / 2;
        coordinates.second = maxLoc.y + component.rows / 2;
    } else {
        return MatchResult();
    }
    return MatchResult(coordinates);
}

void GameScreen::updateScreen(){
    screenshot();
}

MatchResult GameScreen::findComponent(Component c, float accuracy){
    return findComponent(componentPaths[c], accuracy);
}
