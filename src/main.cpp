#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <GameScreen.h>
#include "GateDuel.h"

int main() {
    //while GUI is not ready...
    GameScreen& screen = GameScreen::init(_1280x720, 1.25f); //resolution, zoom
    GateDuel duel(20);
    while (1)
    {
        duel.run();
    }
    return 0;
}