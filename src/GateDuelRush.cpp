#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "GameException.h"
#include "RushDuel.h"
#include "GateDuelRush.h"


void GateDuelRush::run(int level) {
    GameScreen& screen = GameScreen::getInstance();
    RushDuel duel;
    

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
            std::cout << "[INFO] At the gate..." << "\n";
        std::cout << "[INFO] Selecting level and rewards..." << "\n";
        if (screen.waitFor(REWARDS1X_BUTTON, [&]() { return isReward_x1(); }, 5000, 100)){
            screen.waitFor(REWARDS3X_BUTTON, [&]() { return selectReward_x3(); }, 3000, 100);
            if (level == 10)
                screen.waitFor(LVL_10_BUTTON, [&]() { return selectLvl10(); }, 3000, 100);
            else
                screen.waitFor(LVL_20_BUTTON, [&]() { return selectLvl20(); }, 3000, 100);
        }
        
        std::cout << "[INFO] Starting duel..." << std::endl;
        screen.waitFor(DUEL_BUTTON, [&]() { return duel.startRushDuel(); }, 5000, 100);
        screen.waitFor(DIALOGUE_BUTTON, [&]() { return duel.skipDialogue(); }, 5000, 100);
        res = screen.waitFor(DUEL_BUTTON, [&]() { return duel.startRushDuel(); }, 5000, 500);
        screen.sleep(20000);
    }

    int turnCount = 0;
    int monsterCount = 0;
    if (res) std::cout << "[INFO] Duel started. Waiting for initial phase..." << std::endl;
    bool skipBP = false;
    while (!duel.isOver() && turnCount < 16) {        
        turnCount++;
        std::cout << "[INFO] Waiting for player's turn." << std::endl;
        res = screen.waitFor_noexcept(PLAYER_DRAW, [&]() { return duel.draw(); }, 30000, 100);
        if(res) std::cout << "Player drew a card.\n";
        screen.sleep(3000);

        tries = 0;
        while (monsterCount < 3 && tries < 3)
        {
            screen.waitFor_noexcept(DUEL_LOG, [&]() { return duel.selectMonster(); }, 10000, 100);
            res = screen.waitFor_noexcept(NORMAL_SUMMON_BUTTON, [&]() { return duel.normalSummon(); }, 10000, 100);
            if(res){
                std::cout << "Monster is normal summoned.\n";
                monsterCount++;
            }
            else
                tries++;
        }

        if (duel.isPlayerTurnOne() && !duel.isOver()) {
            std::cout << "[INFO] Skipping battle phase...\n";
            skipBP = true;
        }
        
        if(!skipBP){
            if (!duel.isBattlePhase() && !duel.isOver()) {
                std::cout << "[INFO] Switching to battle phase..." << std::endl;
                screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase(); }, 10000, 100);
                if (!screen.waitFor_noexcept(BATTLE_BUTTON, [&]() { return duel.enterBattlePhase(); }, 5000, 100)) {
                    std::cout << "[INFO] Failed to enter battle phase. Ending turn..." << std::endl;
                    res = screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn(); }, 10000, 100);
                    if(res) std::cout << "Turn ended.\n";
                    screen.sleep(7000);
                    continue;
                }
            }
        
            std::cout << "[INFO] Starting attacks..." << std::endl;
            screen.sleep(3000);
            int attacks = 0;
            while (attacks < monsterCount && duel.isBattlePhase() && !duel.isOver()) {
                GameException handler;
                auto attacked = screen.waitFor_noexcept(ATTACK_BUTTON, [&]() { return duel.dragAttack(); }, 10000, 100);
                if(attacked){
                    std::cout << "Attack performed!\n"; 
                    attacks++;
                }
                handler.checkConnectionError();
                screen.sleep(1000);
            }
        }
            
        std::cout << "[INFO] Ending turn..." << std::endl;
        skipBP = false;
        if(!duel.isOver())
            screen.waitFor_noexcept(SELECT_PHASE_BUTTON, [&]() { return duel.selectPhase(); }, 5000, 100);
        if(!duel.isOver()){
            res = screen.waitFor_noexcept(END_TURN_BUTTON, [&]() { return duel.endTurn(); }, 5000, 100);
            if(res) {
                std::cout << "Turn ended\n";
                screen.sleep(10000);
            }
        }
        turnCount++;
    }

    GameException handler;
    std::cout << "[INFO] Duel ended. Confirming result...\n";
    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 10000, 100);
    screen.sleep(3000);

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
