#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"

bool Duel::isDueling(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(DUEL_LOG);
    return result;
}
bool Duel::isPlayerTurn(){
    const std::vector<Component> components = {
        PLAYER_TURN,
        PLAYER_TURN_MP
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.findComponent(component);
        if (result == true)
            return result;
    }
    return false;
}
bool Duel::isDrawPhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(PLAYER_DRAW);
    return result; 
}
bool Duel::draw(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(PLAYER_DRAW, 0.9);
    return result.found; 
}
bool Duel::selectMonster(){
    const std::vector<Component> components = {
        DUEL_LOG, DUEL_LOG_HALF
    };
    GameScreen& screen = GameScreen::getInstance();
    MatchResult result;
    for (const auto& component : components)
    {
        result = screen.getComponentTopCenterCoordinates(DUEL_LOG, 0.9);
        if (result.found)
            break;
        if (!result.found)
            return false;
    }
    int x = result.coordinates.first;
    int y = result.coordinates.second;
    //Find monster position based on duel log postition on screen
    switch (screen.getResolution())
    {
    case _1920x1080:
        x = x-750;
        break;
    case _1600x900:
        x = x-650;
        break;
    case _1280x720:
        x = x-500;
        break;
    }
    screen.click(x, y);
    return result.found; 
}
bool Duel::normalSummon(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(NORMAL_SUMMON_BUTTON, 0.9);
    return result.found; 
}
bool Duel::selectPosition(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(SELECT_POSITION_BUTTON, 0.9);
    return result.found; 
}
bool Duel::selectPhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(SELECT_PHASE_BUTTON, 0.9);
    return result.found; 
}
bool Duel::enterBattlePhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(BATTLE_BUTTON, 0.9);
    return result.found; 
}
bool Duel::selectMonsterToAttack(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent_withMask(HIGHLIGHTED_MONSTER, 0.9);
    return result.found;
}
bool Duel::attack(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(ATTACK_BUTTON, 0.9);
    return result.found; 
}
bool Duel::selectOpponentMonsterToAttack(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent_withMask(OPPONENT_MONSTER_SELECT, 0.9);
    bool finalRes = false;
    if (result.found)
        finalRes = clickConfirmButton();
    return finalRes;
}
bool Duel::clickConfirmButton(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(CONFIRM_BUTTON_BLUE, 0.9);
    return result.found;
}
bool Duel::endTurn(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(END_TURN_BUTTON, 0.9);
    return result.found; 
}
bool Duel::isOver(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(OK_BUTTON, 0.9);
    return result.found; 
}

