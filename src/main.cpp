#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "GameScreen.h"
#include "GateDuel.h"
#include "RaidDuel.h"

int main() {
    //while GUI is not ready...
    GameScreen& screen = GameScreen::init(_1280x720, 1.25f); //resolution, zoom
    GateDuel duel;
    RaidDuel raid;

    std::cout << "Select mode: " << "\n";
    std::cout << "1 - Gate duel" << "\n";
    std::cout << "2 - Raid duel" << "\n";
    
    int ans;
    std::cin >> ans;
    
    switch (ans)
    {
    case 1:
        while (true)
            duel.run(20);
        break;
    case 2:
        while(true)
            raid.run();
        break;
    default:
        std::cout << "Invalid choice!" << "\n";
        break;
    }

    return 0;
}