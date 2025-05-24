#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include "GameScreen.h"
#include "Duel.h"
#include "Util.h"

class MouseEvents {
public:
    void leftClick(int x, int y);
    void rightClick(int x, int y);
    void drag(int x1, int y1, int x2, int y2);
    void clickButton(const Component& button, float accuracy);
};

