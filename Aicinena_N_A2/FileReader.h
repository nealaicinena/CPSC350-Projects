#ifndef FILEREADER_H
#define FILEREADER_H

#include<iostream>
#include<fstream>

using namespace std;

class FileReader {
    public:
        FileReader(); //default constructor
        FileReader(string input, string output); //overloaded constructor of input and output file names
        ~FileReader(); //default destructor
        void outputFile(string o); //outputs the string parameter to the output file
        int *fileInput; //needs to be public so the game can get the information to start the game (total levels, level size, probability of all objects)
    private:
        //private because only need to be accessed by the file reader
        string inputFileName;
        string outputFileName;
        
};

#endif