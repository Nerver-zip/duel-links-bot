#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"

class MouseEvents {
private:
    float scale;
public:
    MouseEvents(float scale);
    void leftClick(int x, int y);
    void clickButton(const Component& button, float accuracy);
};

