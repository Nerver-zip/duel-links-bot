#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "Util.h"
#include "RushDuel.h"

bool RushDuel::isBattlePhase(){
    const std::vector<Component> components = {
        DURING_BATTLE_PHASE6,
        DURING_BATTLE_PHASE7,
        DURING_BATTLE_PHASE8,
        DURING_BATTLE_PHASE9,
        DURING_BATTLE_PHASE10,
        DURING_BATTLE_PHASE11
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.findComponent(component, 0.85);
        if (result.found == true)
            return result.found;
    }
    return false;
}
bool RushDuel::selectPhase(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(SELECT_PHASE_RUSH_BUTTON, 0.9);
    return result.found;
}
bool RushDuel::enterBattlePhase(){
    const std::vector<Component> components = {
        BATTLE_BUTTON,
        BATTLE_BUTTON5,
        BATTLE_BUTTON6,
        BATTLE_BUTTON7
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
bool RushDuel::endTurn(){
    const std::vector<Component> components = {
        END_TURN_BUTTON,
        END_TURN_BUTTON5,
        END_TURN_BUTTON6,
        END_TURN_BUTTON7
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