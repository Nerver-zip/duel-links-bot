#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>

enum Component {
    ARROW_BACK_BUTTON,
    ATTACK_BUTTON,
    BATTLE_BUTTON,
    CLOSE_BUTTON,
    CONFIRM_BUTTON_RED,
    CONNECTION_ERROR_SCREEN,
    DIALOGUE_BUTTON,
    DUEL_BUTTON,
    END_TURN_BUTTON,
    ERROR_SCREEN,
    GATE_BUTTON_MINIMIZED,
    GATE_BUTTON_RED_MINIMIZED,
    GATE_BUTTON_RED,
    GATE_BUTTON_SELECTED_MINIMIZED,
    GATE_BUTTON_SELECTED,
    GATE_BUTTON_STREET_MINIMIZED,
    GATE_BUTTON_STREET,
    GATE_BUTTON,
    LOAD_BLACK,
    LVL_10_BUTTON,
    NEXT_BUTTON,
    NORMAL_SUMMON_BUTTON,
    OK_BUTTON,
    RETRY_BUTTON,
    REWARDS1X_BUTTON_MINIMIZED,
    REWARDS1X_BUTTON,
    SELECT_PHASE_BUTTON,
    SELECT_POSITION_BUTTON,
    SELECT3X_BUTTON
};

struct MatchResult {
    bool found;
    std::pair<int, int> center;
    MatchResult() : found(false), center({-1,-1}) {}
    MatchResult(std::pair<int, int> center) : found(true), center(center) {}
};

class GameScreen {
private:
    cv::Mat src;
    float scale;

    static inline std::unordered_map<Component, std::string> componentPaths = {
        {ARROW_BACK_BUTTON, "assets/arrow_back_button.png"},
        {ATTACK_BUTTON, "assets/attack_button.png"},
        {BATTLE_BUTTON, "assets/battle_button.png"},
        {CLOSE_BUTTON, "assets/close_button.png"},
        {CONFIRM_BUTTON_RED, "assets/confirm_button_red.png"},
        {CONNECTION_ERROR_SCREEN, "assets/connection_error_screen.png"},
        {DIALOGUE_BUTTON, "assets/dialogue_button.png"},
        {DUEL_BUTTON, "assets/duel_button.png"},
        {END_TURN_BUTTON, "assets/end_turn_button.png"},
        {ERROR_SCREEN, "assets/error_screen.png"},
        {GATE_BUTTON_MINIMIZED, "assets/gate_button_minimized.png"},
        {GATE_BUTTON_RED_MINIMIZED, "assets/gate_button_red_minimized.png"},
        {GATE_BUTTON_RED, "assets/gate_button_red.png"},
        {GATE_BUTTON_SELECTED_MINIMIZED, "assets/gate_button_selected_minimized.png"},
        {GATE_BUTTON_SELECTED, "assets/gate_button_selected.png"},
        {GATE_BUTTON_STREET_MINIMIZED, "assets/gate_button_street_minimized.png"},
        {GATE_BUTTON_STREET, "assets/gate_button_street.png"},
        {GATE_BUTTON, "assets/gate_button.png"},
        {LOAD_BLACK, "assets/load_black.png"},
        {LVL_10_BUTTON, "assets/lvl_10_button.png"},
        {NEXT_BUTTON, "assets/next_button.png"},
        {NORMAL_SUMMON_BUTTON, "assets/normal_summon_button.png"},
        {OK_BUTTON, "assets/ok_button.png"},
        {RETRY_BUTTON, "assets/retry_button.png"},
        {REWARDS1X_BUTTON_MINIMIZED, "assets/rewards1x_button_minimized.png"},
        {REWARDS1X_BUTTON, "assets/rewards1x_button.png"},
        {SELECT_PHASE_BUTTON, "assets/select_phase_button.png"},
        {SELECT_POSITION_BUTTON, "assets/select_position_button.png"},
        {SELECT3X_BUTTON, "assets/select3x_button.png"}
    };

    void screenshot();

    MatchResult findComponent(const std::string& path, float accuracy);

public:
    GameScreen(float scale);
    void updateScreen();
    MatchResult findComponent(Component c, float accuracy);
};

#endif