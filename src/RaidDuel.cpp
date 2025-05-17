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
    {
        handler.handleOutlierEvent();
        screen.clickComponent(RAID_BUTTON, 0.85f);
    }

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

    //every once in a while if assist or duel buttons are not found, refresh the event screen
    if (tries == 3 && !screen.findComponent(ASSISTING_PLAYERS, 0.8f).found)
        updateEvent();
        
    auto start = std::chrono::steady_clock::now();
    std::cout << "Dueling!" << "\n";
    while(!duel.isOver() && !screen.findComponent(ASSISTING_PLAYERS, 0.8f).found) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        //this loop will run 3,33 min max
        if(elapsed.count() > 200000){
            std::cout << "Timeout!" << "\n";
            break;
        } 
        screen.sleep(5000);
    }

    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 5000, 100);
    std::cout << "Getting rewards... (if any!)" << "\n";
    while (!isAtRaidEvent() && !screen.findComponent(ASSISTING_PLAYERS, 0.8f).found){
        screen.sleep(2000);
        screen.skip();
        handler.checkConnectionError();
        handler.handleOutlierEvent();
    }
    
    getRewards();
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

void RaidDuel::getRewards(){
    GameScreen& screen = GameScreen::getInstance();
    screen.waitFor(NEXT_BUTTON, [&]() { return screen.clickNextButton(); }, 5000, 100);
    screen.sleep(1000);
    screen.waitFor(NEXT_BUTTON, [&]() { return screen.clickNextButton(); }, 5000, 100);
    screen.waitFor(OK_BUTTON, [&]() { return screen.clickOkButton(); }, 5000, 100);
}
void RaidDuel::updateEvent(){
    GameScreen& screen = GameScreen::getInstance();
    std::cout << "Refreshing event page..." << "\n";
    auto res = screen.clickComponent(DECK_EDITOR_BUTTON, 0.8f).found;
    if (res)
    {
        res = screen.waitFor(COPY_DECK, [&]() { return screen.findComponent(COPY_DECK, 0.8f).found; }, 5000, 100); 
        if(res) 
            screen.waitFor(LOGO, [&]() { return screen.skip(); }, 5000, 100);
        screen.sleep(2000);
    }
    if(screen.findComponent(COPY_DECK, 0.8f).found)
        screen.waitFor(LOGO, [&]() { return screen.skip(); }, 5000, 100);
}