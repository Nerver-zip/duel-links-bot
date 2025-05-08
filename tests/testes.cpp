#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

// Resolução original de captura (Full HD)
const int ORIGINAL_WIDTH = 1920;
const int ORIGINAL_HEIGHT = 1080;

enum Component {
    ARROW_BACK_BUTTON,
    ATTACK_BUTTON,
    BATTLE_BUTTON,
    CLOSE_BUTTON,
    CONFIRM_BUTTON_RED,
    CONNECTION_ERROR_SCREEN,
    CROPPED_CARDS,
    CROPPED_OPPONENT_MONSTER,
    DIALOGUE_BUTTON,
    DUEL_BUTTON,
    DUEL_LOG,
    DUEL_LOG_HALF,
    DURING_BATTLE_PHASE,
    END_TURN_BUTTON,
    ERROR_SCREEN,
    GATE_BUTTON,
    GATE_BUTTON_MINIMIZED,
    GATE_BUTTON_RED,
    GATE_BUTTON_RED_MINIMIZED,
    GATE_BUTTON_SELECTED,
    GATE_BUTTON_SELECTED_MINIMIZED,
    GATE_BUTTON_STREET,
    GATE_BUTTON_STREET_MINIMIZED,
    HIGHLIGHTED_MONSTER,
    IN_GATE,
    INITIATE_LINK,
    LOAD_BLACK,
    LOGO,
    LVL_10_BUTTON,
    NEXT_BUTTON,
    NORMAL_SUMMON_BUTTON,
    OK_BUTTON,
    OPPONENT_MONSTER_SELECT,
    OPPONENT_TURN,
    PLAYER_DRAW,
    PLAYER_TURN,
    PLAYER_TURN_MP,
    REWARDS1X_BUTTON,
    REWARDS1X_BUTTON_MINIMIZED,
    RETRY_BUTTON,
    REWARDS3X_BUTTON,
    SELECT_PHASE_BUTTON,
    SELECT_POSITION_BUTTON,
};

static inline std::unordered_map<Component, std::string> componentPaths = {
    {ARROW_BACK_BUTTON, "../assets/arrow_back_button.png"},
    {ATTACK_BUTTON, "../assets/attack_button.png"},
    {BATTLE_BUTTON, "../assets/battle_button.png"},
    {CLOSE_BUTTON, "../assets/close_button.png"},
    {CONFIRM_BUTTON_RED, "../assets/confirm_button_red.png"},
    {CONNECTION_ERROR_SCREEN, "../assets/connection_error_screen.png"},
    {CROPPED_CARDS, "../assets/cropped_cards.png"},
    {CROPPED_OPPONENT_MONSTER, "../assets/cropped_opponent_monster.png"},
    {DIALOGUE_BUTTON, "../assets/dialogue_button.png"},
    {DUEL_BUTTON, "../assets/duel_button.png"},
    {DUEL_LOG, "../assets/duel_log.png"},
    {DUEL_LOG_HALF, "../assets/duel_log_half.png"},
    {DURING_BATTLE_PHASE, "../assets/during_battle_phase.png"},
    {END_TURN_BUTTON, "../assets/end_turn_button.png"},
    {ERROR_SCREEN, "../assets/error_screen.png"},
    {GATE_BUTTON, "../assets/gate_button.png"},
    {GATE_BUTTON_MINIMIZED, "../assets/gate_button_minimized.png"},
    {GATE_BUTTON_RED, "../assets/gate_button_red.png"},
    {GATE_BUTTON_RED_MINIMIZED, "../assets/gate_button_red_minimized.png"},
    {GATE_BUTTON_SELECTED, "../assets/gate_button_selected.png"},
    {GATE_BUTTON_SELECTED_MINIMIZED, "../assets/gate_button_selected_minimized.png"},
    {GATE_BUTTON_STREET, "../assets/gate_button_street.png"},
    {GATE_BUTTON_STREET_MINIMIZED, "../assets/gate_button_street_minimized.png"},
    {HIGHLIGHTED_MONSTER, "../assets/highlighted_monster.png"},
    {IN_GATE, "../assets/in_gate.png"},
    {INITIATE_LINK, "../assets/initiate_link.png"},
    {LOAD_BLACK, "../assets/load_black.png"},
    {LOGO, "../assets/logo.png"},
    {LVL_10_BUTTON, "../assets/lvl_10_button.png"},
    {NEXT_BUTTON, "../assets/next_button.png"},
    {NORMAL_SUMMON_BUTTON, "../assets/normal_summon_button.png"},
    {OK_BUTTON, "../assets/ok_button.png"},
    {OPPONENT_MONSTER_SELECT, "../assets/opponent_monster_select.png"},
    {OPPONENT_TURN, "../assets/opponent_turn.png"},
    {PLAYER_DRAW, "../assets/player_draw.png"},
    {PLAYER_TURN, "../assets/player_turn.png"},
    {PLAYER_TURN_MP, "../assets/player_turn_mp.png"},
    {RETRY_BUTTON, "../assets/retry_button.png"},
    {REWARDS1X_BUTTON, "../assets/rewards1x_button.png"},
    {REWARDS1X_BUTTON_MINIMIZED, "../assets/rewards1x_button_minimized.png"},
    {REWARDS3X_BUTTON, "../assets/select3x_button.png"},
    {SELECT_PHASE_BUTTON, "../assets/select_phase_button.png"},
    {SELECT_POSITION_BUTTON, "../assets/select_position_button.png"}
};

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

bool findComponentWithMask(const std::string& path, float accuracy, float scale, cv::Point& outCenter, double& confidence) {
    Mat src = capturaTela(scale);
    Mat component = imread(path, IMREAD_UNCHANGED);

    if (component.empty() || component.channels() != 4) {
        std::cerr << "Erro ao carregar componente com canal alpha: " << path << "\n";
        return false;
    }

    // Redimensionamento proporcional baseado na resolução original
    float escalaX = static_cast<float>(src.cols) / ORIGINAL_WIDTH;
    float escalaY = static_cast<float>(src.rows) / ORIGINAL_HEIGHT;
    float escala = std::min(escalaX, escalaY);

    resize(component, component, Size(), escala, escala, INTER_LINEAR);

    std::vector<Mat> channels;
    split(component, channels);
    Mat mask = channels[3]; // canal alpha

    Mat rgbComponent;
    merge(std::vector<Mat>{channels[0], channels[1], channels[2]}, rgbComponent);

    Mat result;
    matchTemplate(src, rgbComponent, result, TM_CCORR_NORMED, mask);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    confidence = maxVal;

    if (maxVal >= accuracy) {
        outCenter = Point(maxLoc.x + rgbComponent.cols / 2, maxLoc.y + rgbComponent.rows / 2);
        return true;
    }

    return false;
}

int main() {
    std::cout << "Iniciando em 3 segundos...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    float scale = 1.25f;
    float accuracy = 0.8f;

    while (true) {
        cv::Point centro;
        double confidence = 0.0;

        bool encontrado = findComponentWithMask(componentPaths[CROPPED_OPPONENT_MONSTER], accuracy, scale, centro, confidence);

        if (encontrado) {
            std::cout << "Botão encontrado em: " << centro.x << ", " << centro.y 
                      << " | Confiança: " << confidence << std::endl;
            clicar(centro.x, centro.y, scale);
        } else {
            std::cout << "Botão NÃO encontrado! | Confiança: " << confidence << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
