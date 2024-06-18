#include "Boss.h"

Boss::Boss() {
    fightWinProb = 50; //50% chance of beating mario
    alive = true; //starts off alive
    powerDecrease = 2; //takes 2 power levels from mario
    letter = 'b'; //b for boss
}

Boss::~Boss() {
    
}