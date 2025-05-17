#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace cv;

enum Resolution {_1920x1080, _1600x900, _1280x720};

static inline std::unordered_map<Resolution, std::pair<float, float>> resolutions = {
    {_1920x1080, {1920.0,1080.0}},
    {_1600x900, {1600.0, 900.0}},
    {_1280x720, {1280.0, 720.0}}
};

Mat src;

Resolution dimensions = _1280x720;
float scale = 1.25; // Fator de escala para a resolução

auto resolution = resolutions[dimensions];

enum Component {
    ARROW_BACK_BUTTON,
    ASSIST_DUEL,
    ASSISTING_PLAYERS,
    ATTACK_BUTTON,
    AUTO_DUEL,
    BATTLE_BUTTON,
    BATTLE_BUTTON2,
    BATTLE_BUTTON3,
    BATTLE_BUTTON4,
    BLANK,
    BLANK2,
    BLANK3,
    BLANK4,
    BLANK5,
    CLOSE_BUTTON,
    CONFIRM_BUTTON_BLUE,
    CONFIRM_BUTTON_RED,
    CONNECTION_ERROR_SCREEN,
    COPY_DECK,
    CROPPED_OPONNENT_MONSTER,
    DECK_EDITOR,
    DECK_EDITOR_BUTTON,
    DIALOGUE_BUTTON,
    DUEL_BUTTON,
    DUEL_LOG,
    DUEL_LOG_HALF,
    DUEL_OVER_DRAW, 
    DUEL_OVER_DRAW2,
    DURING_BATTLE_PHASE,
    DURING_BATTLE_PHASE2,
    DURING_BATTLE_PHASE3,
    DURING_BATTLE_PHASE4,
    DURING_BATTLE_PHASE5,
    DRAW_DECK,
    DRAW_DECK2,
    DRAW_DECK3,
    DRAW_DECK4,
    DRAW_DECK5,
    END_TURN_BUTTON,
    END_TURN_BUTTON2,
    END_TURN_BUTTON3,
    END_TURN_BUTTON4,
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
    HIGHLIGHTED_MONSTER2,
    HIGHLIGHTED_MONSTER3,
    IN_GATE,
    INITIATE_LINK,
    LOAD_BLACK,
    LOGO,
    LVL_10_BUTTON,
    LVL_20_BUTTON,
    NEXT_BUTTON,
    NORMAL_SUMMON_BUTTON,
    OK_BUTTON,
    OPPONENT_FRONTROW,
    OPPONENT_MONSTER1,
    OPPONENT_MONSTER2,
    OPPONENT_MONSTER3,
    OPPONENT_MONSTER_SELECT,
    OPPONENT_WIN, 
    OPPONENT_WIN2,
    OPPONENT_TURN,
    PLAYER_DRAW,
    PLAYER_TURN,
    PLAYER_TURN_MP,
    PLAYER_WIN,
    PLAYER_WIN2,
    RAID_BUTTON,
    RAID_EVENT,
    REWARDS1X_BUTTON,
    REWARDS1X_BUTTON_MINIMIZED,
    RETRY_BUTTON,
    REWARDS3X_BUTTON,
    SELECT_PHASE_BUTTON,
    SELECT_POSITION_BUTTON,
    SELECT_POSITION_BUTTON2,
    SELECT_POSITION_BUTTON3,
    TURN_ONE,
    YES_BUTTON
};



    static inline std::unordered_map<Component, std::string> componentPaths = {
        {ARROW_BACK_BUTTON, "../assets/arrow_back_button.png"},
        {ASSIST_DUEL, "../assets/assist_duel.png"},
        {ASSISTING_PLAYERS, "../assets/assisting_players.png"},
        {ATTACK_BUTTON, "../assets/attack_button.png"},
        {AUTO_DUEL, "../assets/auto_duel.png"},
        {BATTLE_BUTTON, "../assets/battle_button.png"},
        {BATTLE_BUTTON2, "../assets/battle_button2.png"},
        {BATTLE_BUTTON3, "../assets/battle_button3.png"},
        {BATTLE_BUTTON4, "../assets/battle_button4.png"},
        {BLANK, "../assets/blank.png"},
        {BLANK2, "../assets/blank2.png"},
        {BLANK3, "../assets/blank3.png"},
        {BLANK4, "../assets/blank4.png"},
        {BLANK5, "../assets/blank5.png"},
        {CLOSE_BUTTON, "../assets/close_button.png"},
        {CONFIRM_BUTTON_BLUE, "../assets/confirm_button_blue.png"},
        {CONFIRM_BUTTON_RED, "../assets/confirm_button_red.png"},
        {CONNECTION_ERROR_SCREEN, "../assets/connection_error_screen.png"},
        {COPY_DECK, "../assets/copy_deck.png"},
        {DECK_EDITOR, "../assets/deck_editor.png"},
        {DECK_EDITOR_BUTTON, "../assets/deck_editor_button.png"},
        {DIALOGUE_BUTTON, "../assets/dialogue_button.png"},
        {DUEL_BUTTON, "../assets/duel_button.png"},
        {DUEL_LOG, "../assets/duel_log.png"},
        {DUEL_LOG_HALF, "../assets/duel_log_half.png"},
        {DUEL_OVER_DRAW, "../assets/duel_over_draw.png"},
        {DUEL_OVER_DRAW2, "../assets/duel_over_draw2.png"},
        {DUEL_LOG_HALF, "../assets/duel_log_half.png"},
        {DURING_BATTLE_PHASE, "../assets/during_battle_phase.png"},
        {DURING_BATTLE_PHASE2, "../assets/during_battle_phase2.png"},
        {DURING_BATTLE_PHASE3, "../assets/during_battle_phase3.png"},
        {DURING_BATTLE_PHASE4, "../assets/during_battle_phase4.png"},
        {DURING_BATTLE_PHASE5, "../assets/during_battle_phase5.png"},
        {DRAW_DECK, "../assets/draw_deck.png"},
        {DRAW_DECK2, "../assets/draw_deck2.png"},
        {DRAW_DECK3, "../assets/draw_deck3.png"},
        {DRAW_DECK4, "../assets/draw_deck4.png"},
        {DRAW_DECK5, "../assets/draw_deck5.png"},
        {END_TURN_BUTTON, "../assets/end_turn_button.png"},
        {END_TURN_BUTTON2, "../assets/end_turn_button2.png"},
        {END_TURN_BUTTON3, "../assets/end_turn_button3.png"},
        {END_TURN_BUTTON4, "../assets/end_turn_button4.png"},
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
        {HIGHLIGHTED_MONSTER2, "../assets/highlighted_monster2.png"},
        {HIGHLIGHTED_MONSTER3, "../assets/highlighted_monster3.png"},
        {IN_GATE, "../assets/in_gate.png"},
        {INITIATE_LINK, "../assets/initiate_link.png"},
        {LOAD_BLACK, "../assets/load_black.png"},
        {LOGO, "../assets/logo.png"},
        {LVL_10_BUTTON, "../assets/lvl_10_button.png"},
        {LVL_20_BUTTON, "../assets/lvl_20_button.png"},
        {NEXT_BUTTON, "../assets/next_button.png"},
        {NORMAL_SUMMON_BUTTON, "../assets/normal_summon_button.png"},
        {OK_BUTTON, "../assets/ok_button.png"},
        {OPPONENT_FRONTROW, "../assets/opponent_frontrow.png"},
        {OPPONENT_MONSTER1, "../assets/opponent_monster1.png"},
        {OPPONENT_MONSTER2, "../assets/opponent_monster2.png"},
        {OPPONENT_MONSTER3, "../assets/opponent_monster3.png"},
        {OPPONENT_MONSTER_SELECT, "../assets/opponent_monster_select.png"},
        {OPPONENT_TURN, "../assets/opponent_turn.png"},
        {OPPONENT_WIN, "../assets/opponent_win.png"},
        {OPPONENT_WIN2, "../assets/opponent_win2.png"},
        {PLAYER_DRAW, "../assets/player_draw.png"},
        {PLAYER_TURN, "../assets/player_turn.png"},
        {PLAYER_TURN_MP, "../assets/player_turn_mp.png"},
        {PLAYER_WIN, "../assets/player_win.png"},
        {PLAYER_WIN2, "../assets/player_win2.png"},
        {RAID_BUTTON, "../assets/raid_button.png"},
        {RAID_EVENT, "../assets/raid_event.png"},
        {RETRY_BUTTON, "../assets/retry_button.png"},
        {REWARDS1X_BUTTON, "../assets/rewards1x_button.png"},
        {REWARDS1X_BUTTON_MINIMIZED, "../assets/rewards1x_button_minimized.png"},
        {REWARDS3X_BUTTON, "../assets/select3x_button.png"},
        {SELECT_PHASE_BUTTON, "../assets/select_phase_button.png"},
        {SELECT_POSITION_BUTTON, "../assets/select_position_button.png"},
        {SELECT_POSITION_BUTTON2, "../assets/select_position_button2.png"},
        {SELECT_POSITION_BUTTON3, "../assets/select_position_button3.png"},
        {TURN_ONE, "../assets/turn_one.png"},
        {YES_BUTTON, "../assets/yes_button.png"}
    };

Mat updateScreen(float scale) {
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
    bi.biHeight = -adjustedHeight;  // negativo para flip vertical correto
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;

    Mat captured(adjustedHeight, adjustedWidth, CV_8UC3);
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, adjustedHeight, captured.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return captured;
}

Mat resizeComponent(const Mat& original) {
    if (original.empty()) {
        cerr << "Original image is empty in resizeComponent(Mat)" << endl;
        return Mat();
    }

    float ratioX = resolution.first / 1920.0f;
    float ratioY = resolution.second / 1080.0f;
    float ratio = min(ratioX, ratioY);

    Mat resized;
    resize(original, resized, Size(), ratio, ratio, INTER_LINEAR);
    return resized;
}

struct MatchResult {
    pair<int, int> coordinates;
    bool found;

    MatchResult() : coordinates({0, 0}), found(false) {}
    MatchResult(pair<int, int> coords) : coordinates(coords), found(true) {}
};

MatchResult findComponent(const string& path, float accuracy, double& confidence) {
    src = updateScreen(scale);
    Mat component = imread(path);
    confidence = 0.0;

    if (component.empty()) {
        cerr << "Could not find component: " << path << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component);

    Mat result;
    matchTemplate(src, component, result, TM_CCOEFF_NORMED);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    confidence = maxVal;

    if (maxVal >= accuracy) {
        pair<int, int> coordinates = {
            maxLoc.x + component.cols / 2,
            maxLoc.y + component.rows / 2
        };
        return MatchResult(coordinates);
    }

    return MatchResult();
}

MatchResult findComponentWithMask(const string& path, float accuracy, double& confidence) {
    src = updateScreen(scale);
    Mat component = imread(path, IMREAD_UNCHANGED);
    confidence = 0.0;

    if (component.empty() || component.channels() != 4) {
        cerr << "Could not find component with alpha channel: " << path << "\n";
        return MatchResult();
    }

    if (dimensions != _1920x1080)
        component = resizeComponent(component);

    vector<Mat> channels;
    split(component, channels);
    Mat mask = channels[3];
    Mat rgbComponent;
    merge(vector<Mat>{channels[0], channels[1], channels[2]}, rgbComponent);

    if (src.empty() || rgbComponent.empty() || mask.empty()) {
        std::cerr << "One or more mats are empty before matchTemplate." << std::endl;
        return MatchResult();
    }

    Mat result;
    matchTemplate(src, rgbComponent, result, TM_CCORR_NORMED, mask);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    confidence = maxVal;

    if (maxVal >= accuracy) {
        pair<int, int> coordinates = {
            maxLoc.x + rgbComponent.cols / 2,
            maxLoc.y + rgbComponent.rows / 2
        };
        return MatchResult(coordinates);
    }

    return MatchResult();
}

void leftClick(int x, int y, float scale) {

    x = static_cast<int>(x / scale); //off set zoom if any
    y = static_cast<int>(y / scale); 

    SetCursorPos(x, y);

    Sleep(1000);

    INPUT inputDown = {0};
    inputDown.type = INPUT_MOUSE;
    inputDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    INPUT inputUp = {0};
    inputUp.type = INPUT_MOUSE;
    inputUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    INPUT inputs[2] = { inputDown, inputUp };
    UINT sent = SendInput(2, inputs, sizeof(INPUT));
}

// Mutex para proteger o acesso à variável de imagem compartilhada
std::mutex mtx;
Mat displayedImage;

void processComponent(const string& path) {
    while (true) {
        Mat component = imread(path, IMREAD_UNCHANGED);

        // Verificar a resolução antes de exibir
        if (dimensions != _1920x1080) {
            component = resizeComponent(component);
        }

        if (!component.empty()) {
            // Atualizar a variável compartilhada para exibir na thread principal
            mtx.lock();
            displayedImage = component;
            mtx.unlock();
        }

        // Aguarda para simular o tempo de processamento (ajuste conforme necessário)
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    cout << "Iniciando em 3 segundos...\n";
    this_thread::sleep_for(chrono::seconds(3));

    float accuracy = 0.8f; // Precisão para encontrar o componente
    double confidence = 0.0;
    double confidenceMascara = 0.0;

    thread displayThread(processComponent, componentPaths[COPY_DECK]);

    while (true) {
        MatchResult resultadoMascara = findComponentWithMask(componentPaths[COPY_DECK], accuracy, confidenceMascara);
        MatchResult resultadoSemMascara = findComponent(componentPaths[COPY_DECK], accuracy, confidence);

        cout << "--- Comparacao ---\n";
        //if (resultadoMascara.found) {
        //    cout << "[COM mask]     Encontrado em: " 
        //         << resultadoMascara.coordinates.first << ", " 
        //         << resultadoMascara.coordinates.second 
        //         << " | Confianca: " << confidenceMascara << "\n";
        //
        //    if (confidenceMascara >= accuracy) {
        //        leftClick(resultadoMascara.coordinates.first, resultadoMascara.coordinates.second, scale);
        //        cout << "[COM mask]     Clicado!\n";
        //    }
        //} else {
        //    cout << "[COM mask]     NAO encontrado | Confianca: " << confidenceMascara << "\n";
        //}

        if (resultadoSemMascara.found) {
            cout << "[SEM mask]     Encontrado em: " 
                 << resultadoSemMascara.coordinates.first << ", " 
                 << resultadoSemMascara.coordinates.second 
                 << " | Confianca: " << confidence << "\n";

            // Se a confiança for suficiente, faz o clique
            //if (confidence >= accuracy) {
            //    leftClick(resultadoSemMascara.coordinates.first, resultadoSemMascara.coordinates.second, scale);
            //    cout << "[SEM mask]     Clicado!\n";
            //}
        } else {
            cout << "[SEM mask]     NAO encontrado | Confianca: " << confidence << "\n";
        }

        cout << "------------------\n";

        mtx.lock();
        if (!displayedImage.empty()) {
            imshow("My component", displayedImage);
            waitKey(1); 
        }
        mtx.unlock();

        this_thread::sleep_for(chrono::seconds(3));
    }

    displayThread.join();
    return 0;
}
