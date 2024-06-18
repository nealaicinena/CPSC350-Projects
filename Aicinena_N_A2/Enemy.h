#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
using namespace std;

class Enemy {
    public:
        int fightWinProb; //proability of enemy winning against mario
        int powerDecrease; //how much power mario loses if he loses to this enemy
        char letter; //their identifier on the map
};

#endif