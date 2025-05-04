#ifndef DUEL_H
#define DUEL_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>

class Duel {
private:
    float scale;
    static inline std::unordered_map<Component, std::string> componentPaths = {
        {ATTACK_BUTTON, "assets/attack_button.png"},
        {BATTLE_BUTTON, "assets/battle_button.png"},
        {DUEL_BUTTON, "assets/duel_button.png"},
        {END_TURN_BUTTON, "assets/end_turn_button.png"},
        {NORMAL_SUMMON_BUTTON, "assets/normal_summon_button.png"},
        {SELECT_PHASE_BUTTON, "assets/select_phase_button.png"},
        {SELECT_POSITION_BUTTON, "assets/select_position_button.png"},
    };
public:
    Duel(float scale);
    bool startDuel();
    bool selectMonster();
    bool normalSummon();
    bool selectPosition();
    bool selectPhase();
    bool enterBattlePhase();
    bool attack();
    bool endTurn();
};

#endif