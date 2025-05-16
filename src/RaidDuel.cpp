#include "GameScreen.h"
#include "Duel.h"
#include "RaidDuel.h"
#include "GameException.h"

void RaidDuel::run(){
    GameScreen& screen = GameScreen::getInstance();
    GameException handler;
    Duel duel;
    int tries = 0;

    if(!isAtRaidEvent())
        screen.clickComponent(RAID_BUTTON, 0.85f);

    while (!duel.isDueling() && tries < 3) {
        if(screen.findComponent(DUEL_BUTTON, 0.7f).found)
            screen.waitFor(ASSIST_DUEL, [&]() { return screen.clickComponent(DUEL_BUTTON, 0.7f).found; }, 5000, 100);
        else
            screen.waitFor(ASSIST_DUEL, [&]() { return selectAssistDuel(); }, 5000, 100);
        screen.waitFor(DIALOGUE_BUTTON, [&]() { return duel.skipDialogue(); }, 5000, 100);
        screen.waitFor(AUTO_DUEL, [&]() { return duel.startAutoDuel(); }, 5000, 100);
        handler.handleOutlierEvent();
        tries++;
    }

    std::cout << "Dueling!" << "\n";
    while(!duel.isOver()) {
        screen.sleep(5000);
    }

    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 10000, 100);
    
    std::cout << "Getting rewards... (if any!)" << "\n";
    
    while (!isAtRaidEvent() && !screen.findComponent(ASSISTING_PLAYERS, 0.8f).found){
        screen.sleep(1000);
        screen.skip();
        handler.handleOutlierEvent();
    }
    
    screen.waitFor(NEXT_BUTTON, [&]() { return screen.clickNextButton(); }, 5000, 100);
    screen.waitFor(NEXT_BUTTON, [&]() { return screen.clickNextButton(); }, 5000, 100);
    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 5000, 100);
}

bool RaidDuel::isAtRaidEvent(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(RAID_EVENT, 0.8f);
    return result.found;
}

bool RaidDuel::selectAssistDuel(){
    GameScreen& screen = GameScreen::getInstance();
    auto result = screen.clickComponent(ASSIST_DUEL, 0.6f);
    return result.found;
}