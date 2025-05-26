#include "GameScreen.h"
#include "Util.h"
#include "MouseEvents.h"
#include "GameException.h"
#include <thread>
#include <chrono>

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

void GameScreen::sleep(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool GameScreen::waitFor(const Component& c, std::function<bool()> predicate, int timeout_ms, int interval_ms) {
    GameException handler;
    auto start = std::chrono::steady_clock::now();
    while (!predicate()) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        if (elapsed.count() > timeout_ms) {
            std::cerr << "Time out while waiting for " << to_string(c) << "\n";
            return false;
        }
        handler.checkConnectionError();
        sleep(interval_ms);
    }
    return true;
}

bool GameScreen::waitFor_noexcept(const Component& c, std::function<bool()> predicate, int timeout_ms, int interval_ms) {
    auto start = std::chrono::steady_clock::now();
    while (!predicate()) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        if (elapsed.count() > timeout_ms) {
            std::cerr << "Time out while waiting for " << to_string(c) << "\n";
            return false;
        }
        sleep(interval_ms);
    }
    return true;
}

void GameScreen::click(int x, int y){
    MouseEvents mouse;
    mouse.leftClick(x,y);
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
MatchResult GameScreen::findComponent(const std::string& path, float accuracy) {
    src = updateScreen();
    Mat component = imread(path);
    if (component.empty()) {
        std::cerr << "Could not find component: " << path << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component); 

    if (component.empty()) {
        std::cerr << "Component is empty after resizing: " << path << "\n";
        return MatchResult();
    }

    if (src.empty() || component.empty()) {
        std::cerr << "One or more mats are empty before matchTemplate." << std::endl;
        return MatchResult();
    }

    Mat result;
    matchTemplate(src, component, result, TM_CCOEFF_NORMED);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    if (maxVal >= accuracy) {
        std::pair<int, int> coordinates = {
            maxLoc.x + component.cols / 2,
            maxLoc.y + component.rows / 2
        };
        return MatchResult(coordinates);
    }
    return MatchResult();
}

MatchResult GameScreen::findComponentWithMask(const std::string& path, float accuracy) {
    src = updateScreen();
    Mat component = imread(path, IMREAD_UNCHANGED);
    if (component.empty() || component.channels() != 4) {
        std::cerr << "Could not find component with alpha channel: " << path << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component);

    if (component.empty()) {
        std::cerr << "Component is empty after resizing: " << path << "\n";
        return MatchResult();
    }

    if (component.channels() != 4) {
        std::cerr << "Component lost alpha channel after resizing: " << path << "\n";
        return MatchResult();
    }

    std::vector<Mat> channels;
    split(component, channels);
    Mat mask = channels[3];
    Mat rgbComponent;
    merge(std::vector<Mat>{channels[0], channels[1], channels[2]}, rgbComponent);

    if (src.empty() || rgbComponent.empty() || mask.empty()) {
        std::cerr << "One or more mats are empty before matchTemplate." << std::endl;
        return MatchResult();
    }

    Mat result;
    matchTemplate(src, rgbComponent, result, TM_CCORR_NORMED, mask);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    //handle inf and NaN
    if (!std::isfinite(maxVal))
        maxVal = 0.0;

    if (maxVal >= accuracy) {
        std::pair<int, int> coordinates = {
            maxLoc.x + rgbComponent.cols / 2,
            maxLoc.y + rgbComponent.rows / 2
        };
        return MatchResult(coordinates);
    }
    return MatchResult();
}

MatchResult GameScreen::findComponentWithMask(const Component& c, float accuracy){
    src = updateScreen();
    auto path = componentPaths[c];
    Mat component = imread(path, IMREAD_UNCHANGED);
    if (component.empty() || component.channels() != 4) {
        std::cerr << "Could not find component with alpha channel: " << path << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component);

    if (component.empty()) {
        std::cerr << "Component is empty after resizing: " << path << "\n";
        return MatchResult();
    }

    if (component.channels() != 4) {
        std::cerr << "Component lost alpha channel after resizing: " << path << "\n";
        return MatchResult();
    }

    std::vector<Mat> channels;
    split(component, channels);
    Mat mask = channels[3];
    Mat rgbComponent;
    merge(std::vector<Mat>{channels[0], channels[1], channels[2]}, rgbComponent);

    if (src.empty() || rgbComponent.empty() || mask.empty()) {
        std::cerr << "One or more mats are empty before matchTemplate." << std::endl;
        return MatchResult();
    }

    Mat result;
    matchTemplate(src, rgbComponent, result, TM_CCORR_NORMED, mask);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    //handle inf and NaN
    if (!std::isfinite(maxVal))
        maxVal = 0.0;

    if (maxVal >= accuracy) {
        std::pair<int, int> coordinates = {
            maxLoc.x + rgbComponent.cols / 2,
            maxLoc.y + rgbComponent.rows / 2
        };
        return MatchResult(coordinates);
    }
    return MatchResult();
}

Mat GameScreen::updateScreen(){
    screenshot();
    return src;
}

//Buttons were mapped in 1920x1080
//May cause misbehavior the lower the resolution    
Mat GameScreen::resizeComponent(const Mat& original) {
    if (original.empty()) {
        std::cerr << "Original image is empty in resizeComponent(Mat)" << std::endl;
        return Mat();
    }

    auto resolution = resolutions[dimensions];
    float ratioX = resolution.first / 1920.0f;
    float ratioY = resolution.second / 1080.0f;
    float ratio = std::min(ratioX, ratioY);

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

MatchResult GameScreen::getComponentTopCenterCoordinates(const Component& c, float accuracy){
    auto path = componentPaths[c];
    Mat component = imread(path);
    if (component.empty()) {
        std::cerr << "Could not find component." << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component);
    
    Mat result;
    matchTemplate(src, component, result, TM_CCOEFF_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    std::pair<int,int> coordinates;
    if (maxVal >= accuracy) {
        coordinates.first = maxLoc.x + component.cols / 2;
        coordinates.second = maxLoc.y;
    } else {
        return MatchResult();
    }
    return MatchResult(coordinates);
}

MatchResult GameScreen::clickComponent(const Component& c, float accuracy){
    MouseEvents mouse;
    auto result = findComponent(componentPaths[c], accuracy);
    if (result.found)
        mouse.leftClick(result.coordinates.first, result.coordinates.second);
    return result;
}

MatchResult GameScreen::clickComponent_withMask(const Component& c, float accuracy){
    MouseEvents mouse;
    auto result = findComponentWithMask(componentPaths[c], accuracy);
    if (result.found)
        mouse.leftClick(result.coordinates.first, result.coordinates.second);
    return result;
}

bool GameScreen::clickOkButton(){
    MouseEvents mouse;
    auto result = findComponent(componentPaths[OK_BUTTON], 0.8);
    if (result.found)
        mouse.leftClick(result.coordinates.first, result.coordinates.second);
    return result.found;
}

bool GameScreen::clickNextButton(){
    MouseEvents mouse;
    auto result = findComponent(componentPaths[NEXT_BUTTON], 0.8);
    if (result.found)
        mouse.leftClick(result.coordinates.first, result.coordinates.second);
    return result.found;
}

MatchResult GameScreen::clickRetryButton(){
    return clickComponent(RETRY_BUTTON, 0.9);
}

bool GameScreen::skip(){
    MouseEvents mouse;
    auto result = findComponent(componentPaths[LOGO], 0.9);
    if (result.found)
        mouse.rightClick(result.coordinates.first, result.coordinates.second);
    return result.found;
}


