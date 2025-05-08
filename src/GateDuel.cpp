#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "GameException.h"
#include "Duel.h"
#include "GateDuel.h"

void GateDuel::run(){
    GameScreen& screen = GameScreen::getInstance();
    Duel duel;

    while (!duel.isDueling()) {
        if (!isAtGate()) {
            if (!screen.waitFor([&]() { return clickGate(); }, 10000, 200))
                continue;
        }
    
        if (screen.waitFor([&]() { return isReward_x1(); }, 2000, 500)) {
            screen.waitFor([&]() { return selectLvl10(); }, 2000, 500);
            screen.waitFor([&]() { return selectReward_x3(); }, 2000, 500);
        }
    
        screen.waitFor([&]() { return startDuel(); }, 2000, 500);
        screen.waitFor([&]() { return skipDialogue(); }, 1000, 500);
        screen.waitFor([&]() { return startDuel(); }, 2000, 500);
    
        screen.sleep(5000);
    }

    while (!duel.isOver())
    {
        if (!duel.isPlayerTurn()) {
            continue;
        }

        screen.waitFor_noexcept([&]() { return duel.draw();}, 20000, 500);
        screen.waitFor_noexcept([&]() { return duel.selectMonster();}, 20000, 500);
        screen.waitFor_noexcept([&]() { return duel.normalSummon();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectPosition();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectPhase();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.enterBattlePhase();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectMonsterToAttack();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.attack();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectMonsterToAttack();}, 1000, 100);
        screen.waitFor_noexcept([&]() { return duel.attack();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectMonsterToAttack();}, 1000, 100);
        screen.waitFor_noexcept([&]() { return duel.attack();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.selectPhase();}, 1000, 200);
        screen.waitFor_noexcept([&]() { return duel.endTurn();}, 1000, 200);

        screen.sleep(5000);
    }
    screen.waitFor([&]() {return screen.clickOkButton();}, 1000, 500);
    while(!isAtGate() || !foundGateButton()){
        screen.waitFor([&]() {return screen.skip();}, 1000, 500);
    }
}

bool GateDuel::isAtGate(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(IN_GATE);
    return result;
}
bool GateDuel::foundGateButton(){
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
        auto result = screen.findComponent(button);
        if(result)
            return true;
    }
    return false;
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
        auto result = screen.clickComponent(button, 0.9);
        if(result.found)
            return true;
    }
    return false;
}
bool GateDuel::selectLvl10(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(LVL_10_BUTTON, 0.9);
    return result.found;
}
bool GateDuel::isReward_x1(){
    const std::vector<Component> buttons = {
        REWARDS1X_BUTTON, REWARDS1X_BUTTON_MINIMIZED
    };
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(REWARDS1X_BUTTON, 0.9);
    return result.found;
}
bool GateDuel::selectReward_x3(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(REWARDS3X_BUTTON, 0.9);
    return result.found;
}
bool GateDuel::startDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(DUEL_BUTTON, 0.9);
    return result.found;    
}

bool GateDuel::skipDialogue(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(DIALOGUE_BUTTON, 0.9);
    return result.found;
}