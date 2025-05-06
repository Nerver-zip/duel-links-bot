#ifndef UTIL_H
#define UTIL_H

enum Resolution { 
    _1920x1080,
    _1600x900,
    _1280x720
};

enum Component {
    ARROW_BACK_BUTTON,
    ATTACK_BUTTON,
    BATTLE_BUTTON,
    CLOSE_BUTTON,
    CONFIRM_BUTTON_RED,
    CONNECTION_ERROR_SCREEN,
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
    IN_GATE,
    INITIATE_LINK,
    LOAD_BLACK,
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

struct MatchResult {
    bool found;
    std::pair<int, int> coordinates;
    MatchResult() : found(false), coordinates({-1,-1}) {}
    MatchResult(std::pair<int, int> coordinates) : found(true), coordinates(coordinates) {}
};

#endif