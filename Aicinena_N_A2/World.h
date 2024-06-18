#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<random>
#include"Level.h"
#include"Mario.h"
#include "Koopa.h"
#include "Boss.h"
#include "Goomba.h"
//now including all classes to manage their interactions

using namespace std;

class World {
    public:
        World();//default constructor
        World(int marioLives, int levels, int levelSize, int coinProb, 
        int goombaProb, int koopaProb, int mushroomProb, int nothingProb); //overloaded constructor
        ~World(); //default destructor
        string printLevels(); //prints out all the levels for the start of the game
        string placeMario(); //places mario by randomly generating his coordinates
        string moveMario(); //moves mario in a random direction
        string printCurrLevel(); //prints the current level with mario on top
        void addPipes(); //adds all the pipes except for the last level
        void addBosses(); //adds all the bosses
        string checkLocation(); //checks mario's location and his interactions with the spot he is on
        bool gameOver; //public boolean so the game class can know when to end the game
    private:
        //all unsigned because the values cannot be negative and private because they only need to be accessed by the world class
        unsigned int levels;
        unsigned int levelSize; //NxN dimensions of the map
        unsigned int totalMarioMoves;
        unsigned int marioRow; //keeps track of mario's location
        unsigned int marioCol;
        unsigned int currLevel;
        
        Level** myLevels; //array of all the levels for the game
        Mario *myMario; //creates a personal mario to keep track of his data
};

#endif