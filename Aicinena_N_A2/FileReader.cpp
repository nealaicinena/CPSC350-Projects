#include "FileReader.h"

FileReader::FileReader() {
    fileInput = new int[8];
}

FileReader::FileReader(string n, string o) {
    //sets file names to the inputted parameters
    inputFileName = n;
    outputFileName = o;
    fileInput = new int[8]; //creates array of input as 8 because there are 8 lines of information to be read

    ifstream file(inputFileName);
    if(!file.is_open()) { 
        cerr << "Error: unable to open the file" << endl; //if it cannot open the file then show the error
    }

    int i = 0;
    string line;
    while(getline(file, line)) {
        fileInput[i] = stoi(line); //add each line of integers to the array position
        ++i; //increment to the next position
    }
    file.close(); //close the file
}

FileReader::~FileReader() {
    delete[] fileInput; //delete array of the input
}

void FileReader::outputFile(string fileOutput) { //takes in the string wishing to be output to the file
    ofstream outputFile(outputFileName);
    if(!outputFile.is_open()) {
        cerr << "Error: unable to open the output file" << endl; //if it cannot open the file then show the error
    }
    outputFile << fileOutput << endl; //add string information to the output file

    outputFile.close(); //close the file
}