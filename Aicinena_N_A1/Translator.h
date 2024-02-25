#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include<iostream>
#include "Model.h"
using namespace std;

class Translator {
    public:
        Translator(); //default constuctor
        ~Translator(); //default destructor

        //core functions
        string translateEnglishWord(string word);
        string translateEnglishSentence(string sentence);
    private:
        Model *myModel; //create its own model object
};
#endif