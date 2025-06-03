#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "GameException.h"
#include "Duel.h"
#include "GateDuel.h"

void GateDuel::run(int level) {
    GameScreen& screen = GameScreen::getInstance();
    GameException handler;

    Duel duel;

    std::cout << "[INFO] Starting gate duel automation..." << std::endl;
    int tries = 0;
    bool res;
    while (!duel.isDueling() && tries < 3) {
        tries++;
        if (!isAtGate()) {
            std::cout << "[INFO] Not at the gate. Trying to click the gate button..." << std::endl;
            if (!screen.waitFor(GATE_BUTTON, [&]() { return clickGate(); }, 10000, 100)) {
                std::cout << "[WARN] Failed to click the gate button. Retrying..." << std::endl;
                continue;
            }
        }
        else
            std::   cout << "[INFO] At the gate..." << "\n";
            std::cout << "[INFO] Selecting level and rewards..." << "\n";
            if (screen.waitFor(REWARDS1X_BUTTON, [&]() { return isReward_x1(); }, 5000, 100)){
                screen.waitFor(REWARDS3X_BUTTON, [&]() { return selectReward_x3(); }, 3000, 100);
                if (level == 10)
                    screen.waitFor(LVL_10_BUTTON, [&]() { return selectLvl10(); }, 3000, 100);
                else
                    screen.waitFor(LVL_20_BUTTON, [&]() { return selectLvl20(); }, 3000, 100);
            }
        
        std::cout << "[INFO] Starting duel..." << std::endl;
        screen.waitFor(DUEL_BUTTON, [&]() { return duel.startDuel(); }, 5000, 100);
        screen.waitFor(DIALOGUE_BUTTON, [&]() { return duel.skipDialogue(); }, 5000, 100);
        res = screen.waitFor(DUEL_BUTTON, [&]() { return duel.startDuel(); }, 5000, 500);
        screen.sleep(20000);
    }

    int turnCount = 0;
    int monsterCount = 0;
    if (res) std::cout << "[INFO] Duel started. Waiting for initial phase..." << std::endl;
    bool skipBP = false;
    while (!duel.isOver() && turnCount < 10) {
        turnCount++;
        std::cout << "[INFO] Player's turn." << std::endl;
        if (!duel.isPlayerTurnOne() && !duel.isOver()) {
            std::cout << "[INFO] Post-first turn. Performing draw and main plays...\n";
            res = screen.waitFor_noexcept(PLAYER_DRAW, [&]() { return duel.draw(); }, 10000, 100);
            if(res) std::cout << "Player drew a card.\n";
            screen.sleep(3000);
        } else {
            std::cout << "[INFO] First turn. Skipping draw..." << std::endl;
            skipBP = true;
        }

        if (monsterCount < 3)
        {
            screen.waitFor_noexcept(DUEL_LOG, [&]() { return duel.selectMonster(); }, 10000, 100);
            res = screen.waitFor_noexcept(NORMAL_SUMMON_BUTTON, [&]() { return duel.normalSummon(); }, 10000, 100);
            if(res)
                monsterCount++;
            if (monsterCount < 3)
                res = screen.waitFor_noexcept(SELECT_POSITION_BUTTON, [&]() { return duel.selectPosition(); }, 10000, 100);
            if(res){
                std::cout << "Monster is normal summoned.\n";
            } 
        }
        
        if(!skipBP){
            std::cout << "[INFO] Switching to battle phase..." << std::endl;
            screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase(); }, 10000, 100);
            if (!screen.waitFor_noexcept(BATTLE_BUTTON, [&]() { return duel.enterBattlePhase(); }, 5000, 100)) {
                std::cout << "[INFO] Failed to enter battle phase. Ending turn..." << std::endl;
                res = screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn(); }, 10000, 100);
                if(res) std::cout << "Turn ended.\n";
                screen.sleep(4000);
                continue;
            }
        
            std::cout << "[INFO] Starting attacks..." << std::endl;
            int attacks = 0;
            while (attacks < monsterCount && !duel.isOver()) {
                screen.waitFor_noexcept(HIGHLIGHTED_MONSTER, [&]() { return duel.selectMonsterToAttack(); }, 10000, 10);
                auto attacked = screen.waitFor_noexcept(ATTACK_BUTTON, [&]() { return duel.attack(); }, 10000, 100);
                if(attacked){
                    std::cout << "Attack performed!\n"; 
                    attacks++;
                }
                handler.checkConnectionError();
            }
        }
            
        std::cout << "[INFO] Ending turn..." << std::endl;
        skipBP = false;
        if(!duel.isOver()){
            screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase(); }, 5000, 100);
            res = screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn(); }, 5000, 100);
            if(res) {
                std::cout << "Turn ended\n";
                screen.sleep(3000);
            }
        }
        turnCount++;
    }

    std::cout << "[INFO] Duel ended. Confirming result...\n";
    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 10000, 100);

    std::cout << "[INFO] Returning to gate to start next duel..." << "\n";
    tries = 0;
    while (!isAtGate() && !foundGateButton() && tries < 3) {
        res = screen.waitFor(LOGO, [&]() { return screen.skip(); }, 10000, 100);
        if(!res){
            screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 1000, 100);
            tries++;
        }
        handler.checkConnectionError();
        handler.handleOutlierEvent();
        screen.sleep(1000);
    }
    std::cout << "[INFO] Ready for the next duel!" << std::endl;
}   

bool GateDuel::isAtGate(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.findComponent(IN_GATE, 0.80f);
    return result.found;
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
        if(result){
            return true;
        }
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
    auto result = screen.clickComponent(LVL_10_BUTTON, 0.85);
    return result.found;
}
bool GateDuel::selectLvl20(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(LVL_20_BUTTON, 0.85);
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
    auto result = screen.clickComponent(REWARDS3X_BUTTON, 0.8);
    return result.found;
}