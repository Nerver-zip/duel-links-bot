#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "Util.h"

class GameException : public std::exception {
private:
    std::string message;
public:
    GameException() : message("Stopping application") {}
    GameException(const std::string& msg) : message(msg) {}

    inline const char* what() const noexcept override {
        return message.c_str();
    }

    bool checkRunning();
    bool checkConnectionError();
    bool checkGameCrash();
    bool checkFatalError();
    bool handleConnectionError();
    bool handleGameCrash();
    bool handleFatalError();
    bool handleOutlierEvent();
};

#endif