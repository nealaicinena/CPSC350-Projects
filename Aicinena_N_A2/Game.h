#ifndef GAME_H
#define GAME_H

#include<iostream>
#include "World.h"
#include "FileReader.h"
using namespace std;

class Game {
    public:
        Game(); //default constructor
        Game(string inputFile, string outputFile); //overloaded constructor of file names
        ~Game(); //default destructor
        void startGame(); //starts a game of mario

        World *myWorld; //to create our own world environment of the game
        FileReader *myFileReader; //our own file reader to read and write the input and output
};

#endif
