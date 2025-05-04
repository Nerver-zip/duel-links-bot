#ifndef UTIL_H
#define UTIL_H

#include <iostream>

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

#endif