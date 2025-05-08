#ifndef GATEDUEL_H
#define GATEDUEL_H

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include "Util.h"

class GateDuel {
private:
    bool isAtGate();
    bool foundGateButton();
    bool clickGate();
    bool selectLvl10();
    bool isReward_x1();
    bool selectReward_x3();
    bool startDuel();
    bool skipDialogue();
public:
    void run();
};

#endif