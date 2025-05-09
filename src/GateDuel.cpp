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
            if (!screen.waitFor(GATE_BUTTON, [&]() { return clickGate(); }, 10000, 200))
                continue;
        }
    
        if (screen.waitFor(REWARDS1X_BUTTON, [&]() { return isReward_x1(); }, 2000, 500)) {
            screen.waitFor(LVL_10_BUTTON, [&]() { return selectLvl10(); }, 2000, 500);
            screen.waitFor(REWARDS3X_BUTTON, [&]() { return selectReward_x3(); }, 2000, 500);
        }
    
        screen.waitFor(DUEL_BUTTON, [&]() { return startDuel(); }, 3000, 500);
        screen.waitFor(DIALOGUE_BUTTON, [&]() { return skipDialogue(); }, 3000, 500);
        screen.waitFor(DUEL_BUTTON, [&]() { return startDuel(); }, 3000, 500);
    }
    screen.sleep(30000);
    while (!duel.isOver())
    {
        if (!duel.isPlayerTurn()) {
            continue;
        }
        
        if (!duel.isPlayerTurnOne())
        {
            screen.waitFor_noexcept(PLAYER_DRAW, [&]() { return duel.draw();}, 20000, 1000);
            screen.sleep(5000);
            screen.waitFor_noexcept(DUEL_LOG, [&]() { return duel.selectMonster();}, 10000, 1000);
            screen.waitFor_noexcept(NORMAL_SUMMON_BUTTON, [&]() { return duel.normalSummon();}, 2000, 200);
            screen.waitFor_noexcept(SELECT_POSITION_BUTTON, [&]() { return duel.selectPosition();}, 10000, 200);
        }
        else
        {
            screen.waitFor_noexcept(DUEL_LOG, [&]() { return duel.selectMonster();}, 10000, 1000);
            screen.waitFor_noexcept(NORMAL_SUMMON_BUTTON, [&]() { return duel.normalSummon();}, 10000, 200);
            screen.waitFor_noexcept(SELECT_POSITION_BUTTON, [&]() { return duel.selectPosition();}, 10000, 200);
        }

        if (!duel.isBattlePhase())
        {
            screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase();}, 10000, 200);
            if (!screen.waitFor_noexcept(BATTLE_BUTTON, [&]() { return duel.enterBattlePhase();}, 10000, 200))
            {
                screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn();}, 10000, 200);
                screen.sleep(7000);
            }
        }
    
        while (!duel.isBoardCleared() && duel.isBattlePhase())
        {
            screen.waitFor_noexcept(HIGHLIGHTED_MONSTER, [&]() { return duel.selectMonsterToAttack();}, 1000, 200);
            screen.waitFor_noexcept(ATTACK_BUTTON, [&]() { return duel.attack();}, 1000, 200);
            screen.sleep(2000);
        }
    
        screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase();}, 1000, 200);
        screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn();}, 1000, 200);
        screen.sleep(8000);
    }
    screen.waitFor(OK_BUTTON, [&]() {return screen.clickOkButton();}, 1000, 500);
    //get rewards and setup for next duel
    while(!isAtGate() || !foundGateButton()){
        screen.waitFor(LOGO, [&]() {return screen.skip();}, 1000, 500);
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