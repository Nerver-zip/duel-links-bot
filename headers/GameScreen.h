#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <functional>
#include "Util.h"

class GameScreen {
private:
    cv::Mat src;
    Resolution dimensions;
    float scale;

    GameScreen(const Resolution dimensions, float scale);
    static bool initialized;
    static GameScreen instance;

    static inline std::unordered_map<Resolution, std::pair<float, float>> resolutions = {
        {_1920x1080, {1920.0,1080.0}},
        {_1600x900, {1600.0, 900.0}},
        {_1280x720, {1280.0, 720.0}}
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

    void screenshot();

    MatchResult findComponent(const std::string& path, float accuracy);
    cv::Mat resizeComponent(const cv::Mat& original);

public:
    GameScreen(const GameScreen&) = delete;

    static GameScreen& init(const Resolution dimensions, float scale);
    static GameScreen& getInstance();

    void sleep(int ms);
    bool waitFor(const Component& c, std::function<bool()> predicate, int timeout_ms, int interval_ms);
    bool waitFor_noexcept(const Component& c, std::function<bool()> predicate, int timeout_ms, int interval_ms);
    cv::Mat updateScreen();

    Resolution getResolution();
    float getScale();

    MatchResult findComponent(const Component& c, float accuracy);
    MatchResult findComponentWithMask(const std::string& path, float accuracy);
    MatchResult findComponentWithMask(const Component& c, float accuracy);
    MatchResult getComponentTopCenterCoordinates(const Component& c, float accuracy);
    bool findComponent(const Component& c);

    void click(int x, int y);
    bool clickOkButton();
    bool clickNextButton();
    bool skip();

    MatchResult clickComponent(const Component& c, float accuracy);
    MatchResult clickComponent_withMask(const Component& c, float accuracy);
    MatchResult clickCloseButton();
    MatchResult clickConfirmButton();
    MatchResult clickRetryButton();
};

#endif