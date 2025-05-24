#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "GameScreen.h"
#include "GateDuel.h"
#include "GateDuelRush.h"
#include "RaidDuel.h"

int main() {
    //while GUI is not ready...
    GameScreen& screen = GameScreen::init(_1280x720, 1.25f); //resolution, zoom
    GateDuel duel;
    GateDuelRush rushDuel;
    RaidDuel raid;

    std::cout << "Select mode: " << "\n";
    std::cout << "1 - Gate duel (SPEED)" << "\n";
    std::cout << "2 - Gate duel (RUSH)" << "\n";
    std::cout << "3 - Raid duel" << "\n";
    
    int ans;
    std::cin >> ans;
    
    switch (ans)
    {
    case 1:
        while (true)
            duel.run(10);
        break;
    case 2:
        while(true)
            rushDuel.run(10);
        break;
    case 3:
        while(true)
            raid.run(200000);
        break;
    default:
        std::cout << "Invalid choice!" << "\n";
        break;
    }

    return 0;
}