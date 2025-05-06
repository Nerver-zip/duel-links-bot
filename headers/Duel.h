#ifndef DUEL_H
#define DUEL_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>

class Duel {
private:
static inline std::unordered_map<Component, std::string> componentPaths = {
    {ATTACK_BUTTON, "assets/attack_button.png"},
    {BATTLE_BUTTON, "assets/battle_button.png"},
    {DUEL_BUTTON, "assets/duel_button.png"},
    {DUEL_LOG, "assets/duel_log.png"},
    {DUEL_LOG_HALF, "assets/duel_log_half.png"},
    {DURING_BATTLE_PHASE, "assets/during_battle_phase.png"},
    {END_TURN_BUTTON, "assets/end_turn_button.png"},
    {NORMAL_SUMMON_BUTTON, "assets/normal_summon_button.png"},
    {OPPONENT_MONSTER_SELECT, "assets/opponent_monster_select.png"},
    {OPPONENT_TURN, "assets/opp_turn.png"},
    {PLAYER_DRAW, "assets/player_draw.png"},
    {PLAYER_TURN, "assets/player_turn.png"},
    {PLAYER_TURN_MP, "assets/player_turn_mp.png"},
    {SELECT_PHASE_BUTTON, "assets/select_phase_button.png"},
    {SELECT_POSITION_BUTTON, "assets/select_position_button.png"}
};
public:
    bool isDueling();
    bool isPlayerTurn();
    bool isDrawPhase();
    bool draw();
    bool selectMonster();
    bool normalSummon();
    bool selectPosition();
    bool selectPhase();
    bool enterBattlePhase();
    bool attack();
    bool endTurn();
    bool isOver();
};

#endif