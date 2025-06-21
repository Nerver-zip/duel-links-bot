#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include "GameScreen.h"
#include "Util.h"
#include "GameException.h"

bool GameException::checkRunning(){
    if (!GameScreen::getInstance().isRunning())
        throw GameException("Stopping execution...\n");
    return true;
}

bool GameException::checkConnectionError(){
    GameScreen& screen = GameScreen::getInstance();
    screen.updateScreen();
    auto result = screen.findComponent(ERROR_SCREEN, 0.9);
    if(result.found){
       return handleConnectionError();
    }
    return result.found;
}

bool GameException::checkGameCrash(){
    return false;
}
bool GameException::checkFatalError(){
    return false;
}

bool GameException::handleConnectionError(){
    GameScreen& screen = GameScreen::getInstance();
    bool exception = true;
    int count = 0;
    MatchResult solved;
    while (exception)
    {   
        screen.clickRetryButton();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        exception = screen.findComponent(ERROR_SCREEN);
        count++;
        if (count == 100)
            throw GameException("Connection failed.\n");
    }
    return exception;
}

bool GameException::handleGameCrash(){
    return true;
}

bool GameException::handleFatalError(){
    return true;
}

//handles stuff like gift festival that locks the screen until a specific button is pressed
bool GameException::handleOutlierEvent(){
    const std::vector<Component> components = {
        YES_BUTTON,
        CLOSE_BUTTON
    };
    GameScreen& screen = GameScreen::getInstance();
    for (const auto& component : components)
    {
        auto result = screen.clickComponent(component, 0.8);
        if(result.found)
            return true;
    }
    return false;
}
