#include "Game.h"

int main(int argc, char **argv) {
    Game *myGame = new Game("input.txt", argv[1]); //generate new game with input file and output file being represented in the command line (use "output.txt")
    myGame->startGame(); //starts and runs a game while outputting the game information to the output file
    delete myGame; //deletes the game and all objects associated with it
    
    return 0;
}