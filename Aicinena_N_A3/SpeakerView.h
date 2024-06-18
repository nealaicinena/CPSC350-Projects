#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include<iostream>
#include<fstream> //for file reading
#include"MonoStack.h"
#include"GenStack.h"
using namespace std;

class SpeakerView {
    public:
        SpeakerView(); //default constructor
        SpeakerView(string input); //overloaded constructor
        ~SpeakerView(); //destructor

        string checkColumns(); //checks all the columns for height

    private:
        int lines;
        int columns;
        int currCol; //keeps track of current column
        string input;
};
#endif