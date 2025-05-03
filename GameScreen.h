#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>

enum Component{
    OK_BUTTON,
    SUMMON_BUTTON,
    ATTACK_BUTTON,
    SELECT_BUTTON,
    BATTLE_BUTTON,
    END_TURN_BUTTON,
    GATE_BUTTON,
    DUEL_BUTTON,
    ERROR_SCREEN
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
        {OK_BUTTON, "assets/ok_button.png"},
        {SUMMON_BUTTON, "assets/summon_button.png"},
        {ATTACK_BUTTON, "assets/attack_button.png"},
        {SELECT_BUTTON, "assets/select_button.png"},
        {BATTLE_BUTTON, "assets/battle_button.png"},
        {END_TURN_BUTTON, "assets/end_turn_button.png"},
        {GATE_BUTTON, "assets/battle_button.png"},
        {DUEL_BUTTON, "assets/battle_button.png"},
        {ERROR_SCREEN, "assets/error_screen.png"}
    };

    void screenshot();

    MatchResult findComponent(const std::string& path, float accuracy);

public:
    GameScreen(float scale);
    void updateScreen();
    MatchResult findComponent(Component c, float accuracy);
};

#endif