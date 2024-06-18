#include "Enemy.h"

class Boss : public Enemy {
    public :
        Boss(); //default constructor
        ~Boss(); //default destructor
        bool alive; //only for the boss to check if mario beats him since mario gets multiple turns to kill the boss
};