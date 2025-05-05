#include <iostream>
#include "GameScreen.h"
#include "GameException.h"
#include "Duel.h"
#include "GateDuel.h"

GateDuel::GateDuel(){
    //this is where the real fight starts
}

bool GateDuel::isAtGate(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(componentPaths[IN_GATE]);
    return result.found;
}
bool GateDuel::clickGate(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[IN_GATE], 0.9);
    return result.found;
}
bool GateDuel::selectLvl10(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[IN_GATE], 0.9);
    return result.found;
}
bool GateDuel::isReward_x1(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[IN_GATE], 0.9);
    return result.found;
}
bool GateDuel::selectReward_x3(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(componentPaths[IN_GATE], 0.9);
    return result.found;
}
