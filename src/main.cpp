#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <GameScreen.h>
#include "GateDuel.h"

int main() {

    GameScreen& screen = GameScreen::init(_1920x1080, 1.25f);
    GateDuel duel;
    while (1)
    {
        duel.run();
    }

    return 0;
}