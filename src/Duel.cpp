#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"

bool Duel::startDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[DUEL_BUTTON], 0.9);
    return result.found;    
}

bool Duel::selectMonster(){

}
bool Duel::normalSummon(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[NORMAL_SUMMON_BUTTON], 0.9);
    return result.found; 
}
bool Duel::selectPosition(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[SELECT_POSITION_BUTTON], 0.9);
    return result.found; 
}
bool Duel::selectPhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[SELECT_PHASE_BUTTON], 0.9);
    return result.found; 
}
bool Duel::enterBattlePhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[BATTLE_BUTTON], 0.9);
    return result.found; 
}
bool Duel::attack(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[ATTACK_BUTTON], 0.9);
    return result.found; 
}
bool Duel::endTurn(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[END_TURN_BUTTON], 0.9);
    return result.found; 
}

