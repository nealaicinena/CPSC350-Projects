#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<cctype>
using namespace std;

class Model {
    public:
        Model(); //default constructor
        ~Model(); //default destructor
        
        //core functions
        string translateSingleConsonant(char consonant);
        string translateSingleVowel(char vowel);
        bool isVowel(char letter);     
};
#endif