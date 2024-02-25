#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include<iostream>
#include<fstream>
#include "Translator.h"
using namespace std;

class FileProcessor{
    public:
        FileProcessor(); //default constructor
        ~FileProcessor(); //default destructor

        //core functions
        void processFile(string input, string output); //processes file and converts to html in robber translation
        bool isSentence(string input); //checks if string is a sentence
    private:
        Translator *myTranslator; //create its own tranlator object
};
#endif