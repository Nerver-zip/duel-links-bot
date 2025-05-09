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
        {ATTACK_BUTTON, "../assets/attack_button.png"},
        {BATTLE_BUTTON, "../assets/battle_button.png"},
        {CLOSE_BUTTON, "../assets/close_button.png"},
        {CONFIRM_BUTTON_BLUE, "../assets/confirm_button_blue.png"},
        {CONFIRM_BUTTON_RED, "../assets/confirm_button_red.png"},
        {CONNECTION_ERROR_SCREEN, "../assets/connection_error_screen.png"},
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
        {OPPONENT_FRONTROW, "../assets/opponent_frontrow.png"},
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
        {SELECT_POSITION_BUTTON, "../assets/select_position_button.png"},
        {TURN_ONE, "../assets/turn_one.png"}
    };

    void screenshot();

    MatchResult findComponent(const std::string& path, float accuracy);
    cv::Mat resizeComponent(const std::string& path);

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
    MatchResult getComponentTopCenterCoordinates(const Component& c, float accuracy);
    bool findComponent(const Component& c);

    void click(int x, int y);
    bool clickOkButton();
    bool skip();

    MatchResult clickComponent(const Component& c, float accuracy);
    MatchResult clickComponent_withMask(const Component& c, float accuracy);
    MatchResult clickCloseButton();
    MatchResult clickConfirmButton();
    MatchResult clickRetryButton();
};

#endif