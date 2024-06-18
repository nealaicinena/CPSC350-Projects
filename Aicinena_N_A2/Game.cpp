#include "Game.h"

Game::Game() {
    myWorld = new World(); //generates default world
    myFileReader = new FileReader("input.txt", "output.txt"); //opens these default file names (will throw exception if they are not there)
}

Game::Game(string input, string output) { //input of the file names
    myFileReader = new FileReader(input, output); //initializes file reader with the file names
    myWorld = new World(myFileReader->fileInput[0], myFileReader->fileInput[1], myFileReader->fileInput[2], myFileReader->fileInput[3], 
    myFileReader->fileInput[4], myFileReader->fileInput[5], myFileReader->fileInput[6], myFileReader->fileInput[7]); //generates world using the data from the input file
    //each part of the array is a new line from the input file
}

Game::~Game() {
    delete myWorld; //deletes the world
    delete myFileReader; //deletes the file reader
}

void Game::startGame() { //starts a game of mario from start to finish
    string gameOutput = ""; //to store all the output data in a string temporarily
    gameOutput += myWorld->printLevels(); //prints all the levels to start
    myWorld->addPipes(); //adds all the pipes to the levels except the last
    myWorld->addBosses(); //adds bosses to all the levels
    gameOutput += myWorld->placeMario(); //places mario in the beginning level
    while(!myWorld->gameOver) { //while the game is not over, keep playing (until mario loses or wins)
        gameOutput += myWorld->moveMario();
    }
    myFileReader->outputFile(gameOutput);//output to the output file all the info from the game we just played
}