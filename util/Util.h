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

std::string to_string(Component c) {
    switch (c) {
        case ARROW_BACK_BUTTON:               return "ARROW_BACK_BUTTON";
        case ATTACK_BUTTON:                   return "ATTACK_BUTTON";
        case BATTLE_BUTTON:                   return "BATTLE_BUTTON";
        case CLOSE_BUTTON:                    return "CLOSE_BUTTON";
        case CONFIRM_BUTTON_RED:              return "CONFIRM_BUTTON_RED";
        case CONNECTION_ERROR_SCREEN:         return "CONNECTION_ERROR_SCREEN";
        case DIALOGUE_BUTTON:                 return "DIALOGUE_BUTTON";
        case DUEL_BUTTON:                     return "DUEL_BUTTON";
        case DUEL_LOG:                        return "DUEL_LOG";
        case DUEL_LOG_HALF:                   return "DUEL_LOG_HALF";
        case DURING_BATTLE_PHASE:             return "DURING_BATTLE_PHASE";
        case END_TURN_BUTTON:                 return "END_TURN_BUTTON";
        case ERROR_SCREEN:                    return "ERROR_SCREEN";
        case GATE_BUTTON:                     return "GATE_BUTTON";
        case GATE_BUTTON_MINIMIZED:           return "GATE_BUTTON_MINIMIZED";
        case GATE_BUTTON_RED:                 return "GATE_BUTTON_RED";
        case GATE_BUTTON_RED_MINIMIZED:       return "GATE_BUTTON_RED_MINIMIZED";
        case GATE_BUTTON_SELECTED:            return "GATE_BUTTON_SELECTED";
        case GATE_BUTTON_SELECTED_MINIMIZED:  return "GATE_BUTTON_SELECTED_MINIMIZED";
        case GATE_BUTTON_STREET:              return "GATE_BUTTON_STREET";
        case GATE_BUTTON_STREET_MINIMIZED:    return "GATE_BUTTON_STREET_MINIMIZED";
        case IN_GATE:                         return "IN_GATE";
        case INITIATE_LINK:                   return "INITIATE_LINK";
        case LOAD_BLACK:                      return "LOAD_BLACK";
        case LVL_10_BUTTON:                   return "LVL_10_BUTTON";
        case NEXT_BUTTON:                     return "NEXT_BUTTON";
        case NORMAL_SUMMON_BUTTON:            return "NORMAL_SUMMON_BUTTON";
        case OK_BUTTON:                       return "OK_BUTTON";
        case OPPONENT_MONSTER_SELECT:         return "OPPONENT_MONSTER_SELECT";
        case OPPONENT_TURN:                   return "OPPONENT_TURN";
        case PLAYER_DRAW:                     return "PLAYER_DRAW";
        case PLAYER_TURN:                     return "PLAYER_TURN";
        case PLAYER_TURN_MP:                  return "PLAYER_TURN_MP";
        case REWARDS1X_BUTTON:                return "REWARDS1X_BUTTON";
        case REWARDS1X_BUTTON_MINIMIZED:      return "REWARDS1X_BUTTON_MINIMIZED";
        case RETRY_BUTTON:                    return "RETRY_BUTTON";
        case REWARDS3X_BUTTON:                return "REWARDS3X_BUTTON";
        case SELECT_PHASE_BUTTON:             return "SELECT_PHASE_BUTTON";
        case SELECT_POSITION_BUTTON:          return "SELECT_POSITION_BUTTON";
        default:                              return "UNKNOWN_COMPONENT";
    }
}

struct MatchResult {
    bool found;
    std::pair<int, int> coordinates;
    MatchResult() : found(false), coordinates({-1,-1}) {}
    MatchResult(std::pair<int, int> coordinates) : found(true), coordinates(coordinates) {}
};

#endif