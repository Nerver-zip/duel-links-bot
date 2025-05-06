#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "GameException.h"
#include "Duel.h"
#include "GateDuel.h"

GateDuel::GateDuel(){
    //this is where the real fight starts
}

bool GateDuel::isAtGate(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(this->componentPaths[IN_GATE]);
    return result.found;
}
bool GateDuel::clickGate(){
    const std::vector<Component> buttons = {
        GATE_BUTTON,
        GATE_BUTTON_MINIMIZED,
        GATE_BUTTON_RED,
        GATE_BUTTON_RED_MINIMIZED,
        GATE_BUTTON_SELECTED,
        GATE_BUTTON_SELECTED_MINIMIZED,
        GATE_BUTTON_STREET,
        GATE_BUTTON_STREET_MINIMIZED
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& button : buttons)
    {
        auto result = screen.clickComponent(this->componentPaths[button], 0.9);
        if(result.found)
            return true;
    }
    return false;
}
bool GateDuel::selectLvl10(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(this->componentPaths[LVL_10_BUTTON], 0.9);
    return result.found;
}
bool GateDuel::isReward_x1(){
    const std::vector<Component> buttons = {
        REWARDS1X_BUTTON, REWARDS1X_BUTTON_MINIMIZED
    };
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(this->componentPaths[REWARDS1X_BUTTON], 0.9);
    return result.found;
}
bool GateDuel::selectReward_x3(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(this->componentPaths[REWARDS3X_BUTTON], 0.9);
    return result.found;
}
