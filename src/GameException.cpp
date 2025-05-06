#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include "GameScreen.h"
#include "Util.h"
#include "GameException.h"

bool GameException::checkConnectionError(){
    GameScreen& screen = GameScreen::getInstance();
    screen.updateScreen();
    auto result = screen.findComponent(CONNECTION_ERROR_SCREEN, 0.9);
    if(result.found){
       return handleConnectionError();
    }
    return result.found;
}

bool GameException::handleConnectionError(){
    GameScreen& screen = GameScreen::getInstance();
    bool exception = true;
    int count = 0;
    while (exception)
    {   
        screen.clickRetryButton();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        exception = screen.findComponent(CONNECTION_ERROR_SCREEN);
        count++;
        if (count == 100)
            throw std::runtime_error("Connection failed.\n");
    }
}

bool GameException::handleGameCrash(){
    return true;
}

bool GameException::handleFatalError(){
    return true;
}
