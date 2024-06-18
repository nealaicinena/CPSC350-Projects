#include "Level.h"

Level::Level() {
    size = 4; //default size of 4
    //gives each probability a range so coin is between 0-20, goomba is 21-40 and so on
    coinRange = 20;
    goombaRange = 40;
    koopaRange = 60;
    mushroomRange = 80;
    nothingRange = 100;

    map = new char*[size]; //sets array as big as size
    for(int i = 0; i < size; ++i) {
        map[i] = new char[size]; //initializes each array
    }

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            map[i][j] = 'x'; //by default every spot is empty
        }
    }
}

Level::Level(int d, int c, int g, int k, int m, int n) {
    size = d;
    //takes probablilities and adds them up to create the range for each object
    coinRange = c;
    goombaRange = g + coinRange;
    koopaRange = k + goombaRange;
    mushroomRange = m + koopaRange;
    nothingRange = n + mushroomRange;

    map = new char*[size]; //sets array as big as size
    for(int i = 0; i < size; ++i) {
        map[i] = new char[size]; //initializes each array
    }

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            map[i][j] = 'x'; //by default every spot is empty
        }
    }
}

Level::~Level() {
    for(int i = 0; i < size; ++i) {
        delete[] map[i]; //individually deletes each array in map
    }
    delete[] map;//and then deletes the entire map array
}

void Level::populateLevel() {
    std::random_device rd;
    std::mt19937 gen(rd()); //ability to generate random numbers

    std::uniform_int_distribution<int> distribution(1,100); //sets range from 1-100

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            //generates random int for each spot
            int randomValue = distribution(gen);
            //assigns the spot a char based off the random int
            if(randomValue <= coinRange) {
                map[i][j] = 'c';
            } else if(randomValue <= goombaRange) {
                map[i][j] = 'g';
            } else if(randomValue <= koopaRange) {
                map[i][j] = 'k';
            } else if(randomValue <= mushroomRange) {
                map[i][j] = 'm';
            } else if(randomValue <= nothingRange) {
                map[i][j] = 'x';
            }
        }
    }
}

void Level::setObject(int row, int col, char letter) {
    map[row][col] = letter; //specifically sets object at specified spot to a specified char
}

char Level::getObject(int row, int col) {
    return map[row][col]; //returns char at specified spot
}

string Level::printLevel() {
    string levelOutput = "";
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            levelOutput += string(1, map[i][j]) + " "; //prints out each object by converting char to string
        }
        levelOutput += "\n"; //new line for each row
    }
    levelOutput += "==============================\n"; //simple divider to seperate the levels
    return levelOutput;
}

