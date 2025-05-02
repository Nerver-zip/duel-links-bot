#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>

using namespace cv;

enum Component{
    OK_BUTTON,
    SUMMON_BUTTON,
    ATTACK_BUTTON,
    SELECT_BUTTON,
    BATTLE_BUTTON,
    END_TURN_BUTTON,
    GATE_BUTTON,
    DUEL_BUTTON
};

std::unordered_map<Component, std::string> componentPaths = {
    {OK_BUTTON, "assets/ok_button.png"},
    {SUMMON_BUTTON, "assets/summon_button.png"},
    {ATTACK_BUTTON, "assets/attack_button.png"},
    {SELECT_BUTTON, "assets/select_button.png"},
    {BATTLE_BUTTON, "assets/battle_button.png"},
    {END_TURN_BUTTON, "assets/end_turn_button.png"},
    {GATE_BUTTON, "assets/battle_button.png"},
    {DUEL_BUTTON, "assets/battle_button.png"}
};

struct MatchResult {
    bool found;
    std::pair<int, int> center;
    MatchResult() : found(false), center({-1,-1}) {} 
    MatchResult(std::pair<int, int> center) : found(true), center(center) {}
};

class GameScreen {
private:
    Mat src;
    float scale;

    void screenshot() {
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

    MatchResult findComponent(const std::string& path){
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
        if (maxVal >= 0.9) { // Ajuste a sensibilidade aqui
            // Encontra a posição do botão com base na imagem original
            coordinates.first = maxLoc.x + component.cols / 2;
            coordinates.second = maxLoc.y + component.rows / 2;
        } else {
            return MatchResult();
        }
        return MatchResult(coordinates);
    }
public:
    GameScreen(float scale) : scale(scale) {}

    void updateScreen(){
        screenshot();
    }

    MatchResult findComponent(Component c){
        return findComponent(componentPaths[c]);
    }
};

