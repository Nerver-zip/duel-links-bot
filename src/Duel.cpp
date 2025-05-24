#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"
#include "MouseEvents.h"

bool Duel::startDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(DUEL_BUTTON, 0.9);
    return result.found;    
}
bool Duel::startRushDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(RUSH_DUEL, 0.9);
    return result.found;   
}
bool Duel::startAutoDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(AUTO_DUEL, 0.9);
    return result.found;   
}
bool Duel::skipDialogue(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(DIALOGUE_BUTTON, 0.9);
    return result.found;
}
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
    auto result = screen.findComponent(DRAW_DECK);
    return result; 
}
bool Duel::isBattlePhase(){
    const std::vector<Component> components = {
        DURING_BATTLE_PHASE,
        DURING_BATTLE_PHASE2,
        DURING_BATTLE_PHASE3,
        DURING_BATTLE_PHASE4,
        DURING_BATTLE_PHASE5
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.findComponent(component, 0.8);
        if (result.found == true)
            return result.found;
    }
    return false;
}
bool Duel::allAttacksPermormed(){
    const std::vector<Component> components = {
        HIGHLIGHTED_MONSTER,
        HIGHLIGHTED_MONSTER2,
        HIGHLIGHTED_MONSTER3
    };
    GameScreen& screen = GameScreen::getInstance();
    for (int i = 0; i < 50; ++i)
    {
        for (const auto& component : components)
        {
            auto result = screen.findComponentWithMask(component, 0.9);
            if (result.found)
                return false;
        }
    }
    return true;
}
bool Duel::isPlayerTurnOne(){
    const std::vector<Component> components = {
        TURN_ONE,
        TURN_ONE_RUSH
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.findComponent(component, 0.9);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::draw(){
    const std::vector<Component> components = {
        PLAYER_DRAW,
        DRAW_DECK,
        DRAW_DECK2,
        DRAW_DECK3,
        DRAW_DECK4,
        DRAW_DECK5
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.9);
        if (result.found){
            MouseEvents mouse;
            //perform another click 
            screen.sleep(1000);
            mouse.leftClick(result.coordinates.first, result.coordinates.second);
            return true;
        }
    }
    return false;
}
bool Duel::clickBlank(){
    const std::vector<Component> components = {
        BLANK,
        BLANK2,
        BLANK3,
        BLANK4,
        BLANK5
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.9);
        if (result.found)
            return true;
    }
    return false;
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
    const std::vector<Component> components = {
        NORMAL_SUMMON_BUTTON,
        NORMAL_SUMMON_RUSH_BUTTON
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.9);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::selectPosition(){
    const std::vector<Component> components = {
        SELECT_POSITION_BUTTON,
        SELECT_POSITION_BUTTON2,
        SELECT_POSITION_BUTTON3
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.8);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::selectPhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(SELECT_PHASE_BUTTON, 0.9);
    return result.found;
}
bool Duel::enterBattlePhase(){
    const std::vector<Component> components = {
        BATTLE_BUTTON,
        BATTLE_BUTTON2,
        BATTLE_BUTTON3,
        BATTLE_BUTTON4
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.9);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::selectMonsterToAttack(){
    const std::vector<Component> components = {
        HIGHLIGHTED_MONSTER,
        HIGHLIGHTED_MONSTER2,
        HIGHLIGHTED_MONSTER3
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent_withMask(component, 0.8);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::attack(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(ATTACK_BUTTON, 0.9);
    return result.found; 
}
bool Duel::dragAttack(){
    const std::vector<Component> components = {
        HIGHLIGHTED_MONSTER,
        HIGHLIGHTED_MONSTER2,
        HIGHLIGHTED_MONSTER3
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent_withMask(component, 0.8);
        if (result.found){
            MouseEvents mouse;
            mouse.drag(result.coordinates.first, result.coordinates.second, result.coordinates.first, result.coordinates.second - 100);
            return true;
        }
    }
    return false;
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
    const std::vector<Component> components = {
        END_TURN_BUTTON,
        END_TURN_BUTTON2,
        END_TURN_BUTTON3,
        END_TURN_BUTTON4
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.8);
        if (result.found)
            return true;
    }
    return false;
}
bool Duel::isOver(){
    const std::vector<Component> components = {
        PLAYER_WIN,
        PLAYER_WIN2,
        OPPONENT_WIN,
        OPPONENT_WIN2,
        DUEL_OVER_DRAW,
        DUEL_OVER_DRAW2,
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.findComponent(component, 0.93);
        if (result.found == true)
            return result.found;
    }
    return false;
}

