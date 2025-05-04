#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"

Duel::Duel(float scale) : scale(scale) {}

bool Duel::startDuel(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(DUEL_BUTTON, scale);
    return result.found;    
}

bool Duel::selectMonster(){

}
bool Duel::normalSummon(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(NORMAL_SUMMON_BUTTON, scale);
    return result.found; 
}
bool Duel::selectPosition(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(SELECT_POSITION_BUTTON, scale);
    return result.found; 
}
bool Duel::selectPhase(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(SELECT_PHASE_BUTTON, scale);
    return result.found; 
}
bool Duel::enterBattlePhase(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(BATTLE_BUTTON, scale);
    return result.found; 
}
bool Duel::attack(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(ATTACK_BUTTON, scale);
    return result.found; 
}
bool Duel::endTurn(){
    GameScreen& screen = GameScreen::getInstance(scale);
    auto result = screen.clickComponent(END_TURN_BUTTON, scale);
    return result.found; 
}

