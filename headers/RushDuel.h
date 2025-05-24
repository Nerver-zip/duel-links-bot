#ifndef RUSHDUEL_H
#define RUSHDUEL_H

#include "Duel.h"

class RushDuel : public Duel {
public:
    bool isBattlePhase();
    bool selectPhase();
    bool enterBattlePhase();
    bool endTurn();
};

#endif 