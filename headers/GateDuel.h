#ifndef GATEDUEL_H
#define GATEDUEL_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "Util.h"

class GateDuel {
private:
    static inline std::unordered_map<Component, std::string> componentPaths = {
        {DIALOGUE_BUTTON, "assets/dialogue_button.png"},
        {DUEL_BUTTON, "assets/duel_button.png"},
        {GATE_BUTTON_MINIMIZED, "assets/gate_button_minimized.png"},
        {GATE_BUTTON_RED_MINIMIZED, "assets/gate_button_red_minimized.png"},
        {GATE_BUTTON_RED, "assets/gate_button_red.png"},
        {GATE_BUTTON_SELECTED_MINIMIZED, "assets/gate_button_selected_minimized.png"},
        {GATE_BUTTON_SELECTED, "assets/gate_button_selected.png"},
        {GATE_BUTTON_STREET_MINIMIZED, "assets/gate_button_street_minimized.png"},
        {GATE_BUTTON_STREET, "assets/gate_button_street.png"},
        {GATE_BUTTON, "assets/gate_button.png"},
        {IN_GATE, "assets/in_gate.png"},
        {LVL_10_BUTTON, "assets/lvl_10_button.png"},
        {REWARDS1X_BUTTON_MINIMIZED, "assets/rewards1x_button_minimized.png"},
        {REWARDS1X_BUTTON, "assets/rewards1x_button.png"},
        {SELECT3X_BUTTON, "assets/select3x_button.png"}
    };

    bool isAtGate();
    bool clickGate();
    bool selectLvl10();
    bool isReward_x1();
    bool selectReward_x3();

public:
    GateDuel();
};

#endif