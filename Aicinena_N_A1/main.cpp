#include "FileProcessor.h"
#include <fstream>

int main(int argc, char **argv) {
    FileProcessor *myFileProcessor = new FileProcessor; //create new file processor on the heap
    myFileProcessor->processFile("inputFile.txt", "translator.html"); //process these files that are in the folder
    delete myFileProcessor; //garbage collect
    return 0;
}