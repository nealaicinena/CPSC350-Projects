#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <random>
using namespace std;

class Level {
    public:
        Level(); //default constructor
        Level(int size, int coinProb, int goombaProb, 
        int koopaProb, int mushroomProb, int nothingProb); //size of map and all the probabilities of each object spawning
        ~Level(); //default destructor
        void populateLevel(); //used to add all objects to the level
        void setObject(int row, int col, char letter); //set an individual object at specified coordinates
        char getObject(int row, int col); //get an individual object at specified coordinates
        string printLevel(); //print the level map
    private:
        //all unsigned because positive and all private because only the level class needs access to this to populate the levels
        unsigned int size;
        unsigned int coinRange;
        unsigned int goombaRange;
        unsigned int koopaRange;
        unsigned int mushroomRange;
        unsigned int nothingRange;

        char **map; //2D array of the map with all the character representations of the objects

        
};

#endif