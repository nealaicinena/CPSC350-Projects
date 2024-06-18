#include "Mario.h"

Mario::Mario() {
    //default is 1 life and nothing else
    coins = 0;
    lives = 1;
    power = 0;
    defeatedEnemies = 0;
    letter = 'H';
}

Mario::Mario(int i) {
    coins = 0;
    lives = i; //custom lives
    power = 0;
    defeatedEnemies = 0;
    letter = 'H';
}

Mario::~Mario() {

}

int Mario::removeLives(int i) {
    return lives -= i; //decrements lives by i
}

int Mario::addLives(int i) {
    return lives += i; //increments lives by i
}
        
int Mario::removePower(int i) {
    return power -= i; //decrements power by i
}

int Mario::addPower(int i) {
    return power += i; //increments power by i
}
        
string Mario::addCoin() {
    string coinOutput = "";
    ++coins; //adds a coin
    //if you get 20 coins then add another life
    if(coins == 20) { 
        ++lives;
        coins = 0; //reset coins
        coinOutput += "You have collected 20 coins so you gain another life!";
    }
    return coinOutput;
} 

string Mario::killEnemy() { //similar to addCoin method
    string marioOutput = "";
    ++defeatedEnemies; //adds defeated enemy
    //you get another life if you kill 7 enemies
    if(defeatedEnemies == 7) {
        marioOutput += "Mario killed 7 enemies so he gets another life. Mario's current lives";
        marioOutput += lives + "\n";
        ++lives;
        defeatedEnemies = 0; //reset defeated enemies
    }
    return marioOutput;
}

