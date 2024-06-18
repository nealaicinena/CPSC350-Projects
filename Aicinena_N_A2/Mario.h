#ifndef MARIO_H
#define MARIO_H

#include <iostream>
using namespace std;

class Mario {
    public:
        Mario(); //default constructor
        Mario(int lives); //overloaded constructor with mario's lives as parameter
        ~Mario(); //default destructor

        //all unsigned because non negative
        unsigned int lives;
        unsigned int power;
        unsigned int coins;
        unsigned int defeatedEnemies; //keeps track of mario's total kills
        char letter; //mario's assigned letter on the grid

        int removeLives(int lives); //removes desired amount of lives
        int addLives(int lives); //adds desired amount of lives
        int removePower(int power); //removes desired amount of power
        int addPower(int power); //adds desired amount of power
        string addCoin();  //adds 1 coin
        string killEnemy(); //adds to defeated enemies
};

#endif