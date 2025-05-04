#include "GameScreen.h"
#include "Util.h"
#include "MouseEvents.h"

using namespace cv;

GameScreen GameScreen::instance(_1920x1080, 0.9);
bool GameScreen::initialized = false;

GameScreen::GameScreen(const Resolution dimensions, float scale) : dimensions(dimensions), scale(scale) {}

GameScreen& GameScreen::init(const Resolution dimensions, float scale) {
    if(!initialized){
        instance = GameScreen(dimensions, scale);
        initialized = true;
    }
    else
        std::cerr << "GameScreen already initialized" << "\n";
    return instance;
}

GameScreen& GameScreen::getInstance() {
    return instance;
}

Resolution GameScreen::getResolution(){
    return this->dimensions;
}

float GameScreen::getScale(){
    return this->scale;
}

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
        std::cerr << "Could not find component." << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(path);
    
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

Mat GameScreen::updateScreen(){
    screenshot();
    return src;
}

//Buttons were mapped in 1920x1080, we try to resize in order to find
//May cause misbehavior the lower the resolution
Mat GameScreen::resizeComponent(const std::string& path){
    Mat original = imread(path);
    
    auto resolution = resolutions[dimensions];
    float width = resolution.first;
    float height = resolution.second;

    float ratioX = static_cast<float>(width) / 1920.0;
    float ratioY = static_cast<float>(height) / 1080.0;
    float ratio = min(ratioX, ratioY); 

    Mat resized;
    resize(original, resized, Size(), ratio, ratio, INTER_LINEAR);
    return resized;
}

MatchResult GameScreen::findComponent(const Component& c, float accuracy){
    return findComponent(componentPaths[c], accuracy);
}

bool GameScreen::findComponent(const Component& c){
    auto result = findComponent(componentPaths[c], 0.9);
    return result.found;
}

MatchResult GameScreen::clickComponent(const Component& c, float accuracy){
    MouseEvents mouse;
    auto result = findComponent(componentPaths[c], accuracy);
    if (result.found)
        mouse.leftClick(result.center.first, result.center.second);
    return result;
}

