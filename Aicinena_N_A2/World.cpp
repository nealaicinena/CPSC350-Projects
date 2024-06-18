#include "World.h"

World::World() {
    myMario = new Mario(); //creates default mario
    //all the default variables to the maps and total levels
    totalMarioMoves = 0; //starting moves initialized to 0
    levels = 2; 
    levelSize = 3;
    currLevel = 0; //starting on current level
    gameOver = false; //game is false until win or lose
    myLevels = new Level*[levels]; //initializes all the levels
    for(int i = 0; i < levels; ++i) {
        Level *newLevel = new Level(); //creates level object
        newLevel->populateLevel(); //populates level
        myLevels[i] = newLevel; //sets each level in the array equal to a randomly populated level
    }
}

World::World(int i, int l, int s, int c, int g, int k, int m, int n) {
    myMario = new Mario(i); //creates mario with custom lives
    totalMarioMoves = 0; //starting moves initialized to 0
    //sets level info equal to the input
    levels = l;
    levelSize = s;
    currLevel = 0; //starting on current level
    gameOver = false; //game over is false until win or lose
    myLevels = new Level*[levels]; //initializes all the levels
    for(int i = 0; i < levels; ++i) {
        Level *newLevel = new Level(levelSize, c, g, k, m, n); //creates level object
        newLevel->populateLevel(); //populates level
        myLevels[i] = newLevel; //sets each level in the array equal th a randomly populated level
    }
}

World::~World() {
    for(int i = 0; i < levels; i++) {
        delete myLevels[i]; //deletes each level
    }
    delete myMario; //deletes mario
    delete myLevels; //deletes the array of levels
}

string World::placeMario() {
    string placingOutput = "";
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(0, levelSize - 1); //allows to generate int from 0 to the level size
    
    marioRow = distribution(gen); //random row position for mario
    marioCol = distribution(gen); //random column position for mario
    if(totalMarioMoves == 0) { //if this is the start of the game then print out the starting position
        placingOutput += "Mario is starting in position: (" + to_string(marioRow) + "," + to_string(marioCol) + ")\n";
        placingOutput += printCurrLevel(); //print current level to see start of game
    }
    placingOutput += checkLocation(); //check where mario has spawned incase he is on top of an object
    return placingOutput;
}

string World::moveMario() {
    string movingOutput = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 4); //allows to generate int from 1-4 to simulate the 4 directions mario can move
    int direction = distribution(gen);

    if(direction == 1) { //down
        movingOutput += "Mario will move down\n";
        if(marioRow == levelSize - 1) { //if on the bottom of the level then wrap to the top
            marioRow = 0;
        } else {
            ++marioRow; //otherwise move down
        }
    } else if(direction == 2) { //up
        movingOutput += "Mario will move up\n";
        if(marioRow == 0) { //if on the top of the level then wrap to the bottom
            marioRow = levelSize - 1;
        } else {
            --marioRow; //otherwise move up
        }    
    } else if(direction == 3) { //right
        movingOutput += "Mario will move right\n";
        if(marioCol == levelSize - 1) { //if on the right of the map then wrap to the left
            marioCol = 0;
        } else {
            ++marioCol; //otherwise move right
        }
    } else if(direction == 4) { //left
        movingOutput += "Mario will move left\n";
        if(marioCol == 0) { //if on the left of the map them wrap to the right
            marioCol = levelSize - 1;
        } else {
            --marioCol; //otherwise move left
        }
    }
    ++totalMarioMoves; //add one move to mario's total moves
    movingOutput += printCurrLevel(); //print out the map where mario currently is
    movingOutput += checkLocation(); // check where mario has moved to incase he has landed on something
    return movingOutput;
}

void World::addPipes() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(0, levelSize - 1); //allows to generate from 1 to level size (same as we did for mario)

    int pipeRow;
    int pipeCol;
    
    for(int i = 0; i < levels - 1; ++i) { //for every level (except the last) generate row and column coordinates
        pipeRow = distribution(gen);
        pipeCol = distribution(gen);
        myLevels[i]->setObject(pipeRow, pipeCol, 'w'); //set the object of this level to a warp pipe
    }
}

void World::addBosses() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(0, levelSize - 1); //allows to generate from 1 to level size (same as add pipes)

    int bossRow;
    int bossCol;
    
    for(int i = 0; i < levels; ++i) { //for all levels, even the last one, generate row and column for boss
        bossRow = distribution(gen);
        bossCol = distribution(gen);
        myLevels[i]->setObject(bossRow, bossCol, 'b'); // sets this object of the level to the boss
    }
}

string World::checkLocation() {
    string output = "";
    //returns all the basic info of where mario is: level, position, and power level
    output += "Level: " + to_string(currLevel) + ". ";
    output += "Mario is at position: (" + to_string(marioRow) + "," + to_string(marioCol) + "). ";
    output += "Mario is at power level " + to_string(myMario->power) + ".\n";
    if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'c') { //if mario lands on a coin
        output += myMario->addCoin(); //add coin
        output += "Mario found a coin. ";
        myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove coin from the level
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'm') { //if mario lands on a mushroom
        if(myMario->power == 2) { //if mario is already on max power then do nothing
            output += "Mario picks up a mushroom but already has max power\n";
        } else { //otherwise add power to mario
            myMario->addPower(1);
            output += "Mario picks up a mushroom. ";
            myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove the mushroom from the level
        }
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'k') { //if mario lands on a koopa
        output += "Mario has encountered a koopa ";
        Koopa *myKoopa = new Koopa(); //construct a koopa
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 100); //allows to generate int from 1 to 100 for the fighting odds

        int success = distribution(gen); //randomly sees if mario won
        if(success > myKoopa->fightWinProb) { //if success is greater than the odds of koopa winning
            output += myMario->killEnemy(); //add a kill to mario's total
            output += "and won. ";
            myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove the koopa from the map
        } else { //if mario loses...
            if(myMario->power > 0) { //if mario has some power then just remove power level
                myMario->removePower(myKoopa->powerDecrease);
                output += "and lost.\n";

            } else { //if mario has no power level left
                if(myMario->lives > 1) { //if mario has some lives still though
                    myMario->removeLives(1); //remove 1 life from mario
                    output += "and lost. \n";
                } else { //if mario runs out of lives
                    myMario->removeLives(1); //set lives to 0
                    //let the user know the game is over and lost
                    output += "and lost.\n";
                    output += "We lost the game :(\n";
                    output += "total moves: " + to_string(totalMarioMoves) + "\n";
                    gameOver = true; //end the game
                }  
            }
        }
        delete myKoopa; //get rid of the koopa object after the battle
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'g') { //if mario lands on a goomba
        output += "Mario encountered a goomba ";
        Goomba *myGoomba = new Goomba(); //create a goomba object
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 100); //allows to generate outcome of the battle

        int success = distribution(gen); //randomly sees if mario won
        if(success > myGoomba->fightWinProb) { //if success is greater than the odds of the goomba winning
            output += myMario->killEnemy(); //add a kill to mario's total
            myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove the goomba from the level
            output += "and won. ";
        } else { //if mario loses
            if(myMario->power > 0) { //if mario has some power then just remove power level
                myMario->removePower(myGoomba->powerDecrease);
                output += "and lost. ";
            } else { //if mario has no power levels left
                if(myMario->lives > 1) { //if mario has some lives still though
                    myMario->removeLives(1); //remove 1 life from mario
                    output += "and lost. ";
                } else { //if mario runs out of lives
                    myMario->removeLives(1); //set lives to 0
                    //let the user know the game is over and lost
                    output += "and lost. \n";
                    output += "We lost the game :(\n";
                    output += "total moves: " + to_string(totalMarioMoves) + "\n";
                    gameOver = true; //end the game
                }  
            }
        }
        delete myGoomba; //get rid of the koopa object after the battle
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'b') { //if mario lands on a boss
        Boss *myBoss = new Boss(); //create a goomba object
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 100); //allows to generate outcome of the battle
        while(myBoss->alive) { //keep fighting until the boss dies or we lose
            output += "Mario has encountered the level boss ";
            int success = distribution(gen); //randomly sees if mario won
            if(success > myBoss->fightWinProb) { //if success is greater than the odds of the boss winning
                if(currLevel == levels - 1) { //if this is the final boss (aka the last level)
                    output += myMario->killEnemy(); //add a kill to mario's total
                    myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove the boss from the level
                    //let the user know the game is over and won
                    output += "and won.\n";
                    output += "WE BEAT THE GAME! :)\n";
                    output += "total moves: " + to_string(totalMarioMoves) + "\n";
                    gameOver = true; //end the game
                    myBoss->alive = false; //kill the boss
                } else { // if this is not the last level
                    output += myMario->killEnemy(); //add a kill to mario's total
                    myLevels[currLevel]->setObject(marioRow, marioCol, 'x'); //remove the boss from the level
                    output += "and won. ";
                    ++currLevel; //increment to the next level
                    output += "Level: " + to_string((currLevel + 1)) + "\n";
                    placeMario(); //randomly place mario in the new level
                    myBoss->alive = false; //kill the boss to get out of the loop
                }
            } else { //if mario loses
                if(myMario->power > 1) { //if mario has power level of 2
                    myMario->removePower(myBoss->powerDecrease); //remove 2 power levels because this is the boss
                    output += "and lost.\n";
                    output += "Mario will stay put and try again\n";
                    //do not kill boss because mario will try again without moving on
                } else { //if mario does not have enough power
                    if(myMario->lives > 1) { //if mario has some lives to work with
                        myMario->power = 0; //take away all his power from being attacked
                        myMario->removeLives(1); //remove a life because he does not have enough power
                        output += "and lost.\n";
                        output += "Mario will stay put and try again\n";
                        //do not kill boss because mario will try again without moving on
                    } else { //if mario has no more lives
                        myMario->power = 0; //remove all his power
                        myMario->removeLives(myBoss->powerDecrease); //set his lives to 0
                        //let the user know the game is over and lost
                        output += "and lost.\n.";
                        output += "We lost the game :(\n";
                        output += "total moves: " + to_string(totalMarioMoves) + "\n";
                        gameOver = true; //end the game
                        myBoss->alive = false; //kill the boss to get out of the loop
                    }  
                }
            }
        }
        delete myBoss; //get rid of the boss object after the battle
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'w') { //if mario lands on a warp pipe
        output += "Mario found a warp pipe. ";
        ++currLevel; //move onto the next level
        placeMario(); //randomly place mario in the new level
        output += "Current level: ";
        output += to_string((currLevel)) + "\n";
    } else if(myLevels[currLevel]->getObject(marioRow, marioCol) == 'x') { //if mario lands on nothing
        output += "The position is empty. "; //just let the user know nothing happened
    }
    output += "Mario has " + to_string(myMario->lives) + " lives left. Mario has " + to_string(myMario->coins) + " coins.\n"; //summary of mario's stats after all the possible interactions
    return output;
}

string World::printLevels() { //prints all the levels (used for the start of the game)
    string printLevelsOutput = "";
    for(int i = 0; i < levels; ++i) { //increments through all the levels
        printLevelsOutput += myLevels[i]->printLevel(); //prints each level
    }
    return printLevelsOutput;
}

string World::printCurrLevel() { //prints only the level mario is currently on
    string output = "";
    output += "=============================\n";
    char temp = myLevels[currLevel]->getObject(marioRow, marioCol); //stores the object where mario's coordinates are on top of
    myLevels[currLevel]->setObject(marioRow, marioCol, myMario->letter); //temporarily set that spot equal to mario's character so the user knows where he is when the level is printed
    output += myLevels[currLevel]->printLevel(); //print out the level with mario in it
    myLevels[currLevel]->setObject(marioRow, marioCol, temp); //set back the spot to the original object
    return output;
}