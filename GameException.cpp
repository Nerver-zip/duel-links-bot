#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include "GameScreen.h"
#include "Util.h"
#include "GameException.h"

GameException::GameException(float scale) : scale(scale) {}

bool GameException::checkConnectionError(){
    GameScreen& screen = GameScreen::getInstance(scale);
    screen.updateScreen();
    auto result = screen.findComponent(CONNECTION_ERROR_SCREEN, 0.9);
    return result.found;
}

bool GameException::handleConnectionError(){
    GameScreen& screen = GameScreen::getInstance(scale);
    bool exception = true;
    int count = 0;
    while (exception)
    {   
        screen.clickRetryButton();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        exception = screen.findComponent(CONNECTION_ERROR_SCREEN);
        count++;
        if (count == 100)
            throw std::runtime_error("Connection failed. Exiting program.\n");
    }
}

bool GameException::handleGameCrash(){
    return true;
}

bool GameException::handleFatalError(){
    return true;
}
