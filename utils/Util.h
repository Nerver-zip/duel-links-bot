#ifndef UTIL_H
#define UTIL_H

enum Resolution { 
    _1920x1080,
    _1600x900,
    _1280x720
};

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
    BATTLE_BUTTON5,
    BATTLE_BUTTON6,
    BATTLE_BUTTON7,
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
    DURING_BATTLE_PHASE6,
    DURING_BATTLE_PHASE7,
    DURING_BATTLE_PHASE8,
    DURING_BATTLE_PHASE9,
    DURING_BATTLE_PHASE10,
    DURING_BATTLE_PHASE11,
    DRAW_DECK,
    DRAW_DECK2,
    DRAW_DECK3,
    DRAW_DECK4,
    DRAW_DECK5,
    END_TURN_BUTTON,
    END_TURN_BUTTON2,
    END_TURN_BUTTON3,
    END_TURN_BUTTON4,
    END_TURN_BUTTON5,
    END_TURN_BUTTON6,
    END_TURN_BUTTON7,
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
    IN_GAME_AUTO_DUEL,
    INITIATE_LINK,
    LOAD_BLACK,
    LOGO,
    LVL_10_BUTTON,
    LVL_20_BUTTON,
    NEXT_BUTTON,
    NORMAL_SUMMON_BUTTON,
    NORMAL_SUMMON_RUSH_BUTTON,
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
    REWARDS3X_WHITE_BUTTON,
    RUSH_DUEL,
    SELECT_PHASE_BUTTON,
    SELECT_PHASE_RUSH_BUTTON,
    SELECT_POSITION_BUTTON,
    SELECT_POSITION_BUTTON2,
    SELECT_POSITION_BUTTON3,
    TURN_ONE,
    TURN_ONE_RUSH,
    YES_BUTTON
};

inline std::string to_string(Component c) {
    switch (c) {
        case ARROW_BACK_BUTTON:               return "ARROW_BACK_BUTTON";
        case ASSIST_DUEL:                     return "ASSIST_DUEL BUTTON";
        case ATTACK_BUTTON:                   return "ATTACK_BUTTON";
        case AUTO_DUEL:                       return "AUTO_DUEL";
        case BATTLE_BUTTON:                   return "BATTLE_BUTTON";
        case CLOSE_BUTTON:                    return "CLOSE_BUTTON";
        case CONFIRM_BUTTON_BLUE:             return "CONFIRM_BUTTON_BLUE";
        case CONFIRM_BUTTON_RED:              return "CONFIRM_BUTTON_RED";
        case CONNECTION_ERROR_SCREEN:         return "CONNECTION_ERROR_SCREEN";
        case CROPPED_OPONNENT_MONSTER:        return "CROPPED_OPONNENT_MONSTER";
        case DIALOGUE_BUTTON:                 return "DIALOGUE_BUTTON";
        case DUEL_BUTTON:                     return "DUEL_BUTTON";
        case DUEL_LOG:                        return "DUEL_LOG";
        case DUEL_LOG_HALF:                   return "DUEL_LOG_HALF";
        case DUEL_OVER_DRAW:                  return "DUEL_OVER_DRAW";
        case DUEL_OVER_DRAW2:                 return "DUEL_OVER_DRAW";
        case DURING_BATTLE_PHASE:             return "DURING_BATTLE_PHASE";
        case END_TURN_BUTTON:                 return "END_TURN_BUTTON";
        case END_TURN_BUTTON2:                return "END_TURN_BUTTON";
        case END_TURN_BUTTON3:                return "END_TURN_BUTTON";
        case END_TURN_BUTTON4:                return "END_TURN_BUTTON";
        case ERROR_SCREEN:                    return "ERROR_SCREEN";
        case GATE_BUTTON:                     return "GATE_BUTTON";
        case GATE_BUTTON_MINIMIZED:           return "GATE_BUTTON_MINIMIZED";
        case GATE_BUTTON_RED:                 return "GATE_BUTTON_RED";
        case GATE_BUTTON_RED_MINIMIZED:       return "GATE_BUTTON_RED_MINIMIZED";
        case GATE_BUTTON_SELECTED:            return "GATE_BUTTON_SELECTED";
        case GATE_BUTTON_SELECTED_MINIMIZED:  return "GATE_BUTTON_SELECTED_MINIMIZED";
        case GATE_BUTTON_STREET:              return "GATE_BUTTON_STREET";
        case GATE_BUTTON_STREET_MINIMIZED:    return "GATE_BUTTON_STREET_MINIMIZED";
        case HIGHLIGHTED_MONSTER:             return "HIGHLIGHTED_MONSTER";
        case IN_GATE:                         return "IN_GATE";
        case INITIATE_LINK:                   return "INITIATE_LINK";
        case LOAD_BLACK:                      return "LOAD_BLACK";
        case LOGO:                            return "LOGO";
        case LVL_10_BUTTON:                   return "LVL_10_BUTTON";
        case LVL_20_BUTTON:                   return "LVL_20_BUTTON";
        case NEXT_BUTTON:                     return "NEXT_BUTTON";
        case NORMAL_SUMMON_BUTTON:            return "NORMAL_SUMMON_BUTTON";
        case OK_BUTTON:                       return "OK_BUTTON";
        case OPPONENT_FRONTROW:               return "OPPONENT_FRONTROW";
        case OPPONENT_MONSTER_SELECT:         return "OPPONENT_MONSTER_SELECT";
        case OPPONENT_TURN:                   return "OPPONENT_TURN";
        case OPPONENT_WIN:                    return "OPPONENT_WIN";
        case OPPONENT_WIN2:                   return "OPPONENT_WIN";
        case PLAYER_DRAW:                     return "PLAYER_DRAW";
        case PLAYER_TURN:                     return "PLAYER_TURN";
        case PLAYER_TURN_MP:                  return "PLAYER_TURN_MP";
        case PLAYER_WIN:                      return "PLAYER_WIN";
        case RAID_BUTTON:                     return "RAID_BUTTON";
        case RAID_EVENT:                      return "RAID_EVENT";
        case REWARDS1X_BUTTON:                return "REWARDS1X_BUTTON";
        case REWARDS1X_BUTTON_MINIMIZED:      return "REWARDS1X_BUTTON_MINIMIZED";
        case RETRY_BUTTON:                    return "RETRY_BUTTON";
        case REWARDS3X_BUTTON:                return "REWARDS3X_BUTTON";
        case RUSH_DUEL:                       return "RUSH_DUEL_BUTTON";
        case SELECT_PHASE_BUTTON:             return "SELECT_PHASE_BUTTON";
        case SELECT_POSITION_BUTTON:          return "SELECT_POSITION_BUTTON";
        case TURN_ONE:                        return "TURN ONE";
        case YES_BUTTON:                      return "YES BUTTON";
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