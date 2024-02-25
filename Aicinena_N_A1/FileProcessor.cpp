#include "FileProcessor.h"
#include "Translator.h"

FileProcessor::FileProcessor() {
    myTranslator = new Translator; //add translator to the heap
}

FileProcessor::~FileProcessor() {
    delete myTranslator; //garbage collect by deleting myTranslator
}

bool FileProcessor::isSentence(string input) {
    for (char character : input){ //goes through each char of string
        if (character == ' '){
            return true; //if theres a space (its a sentence) then return true
        }
    }
    return false; //if not, return false
}

void FileProcessor::processFile(string input, string output){ //takes in name of input output file
    //declare strings to be used later for translation
    string inputString = "";
    string translateString = "";
    string fileContents = "";

    //open reading file
    ifstream inFile;
    inFile.open(input);

    //open writing file
    ofstream outFile;
    outFile.open(output);

    //add head and title before translation if writing file is open
    if (outFile.is_open()){
        outFile << "!<DOCTYPE html>";
        outFile << "<html>\n";
        outFile << "<head>\n";
        outFile << "<title>English to Robber Translation</title>\n";
        outFile << "</head>\n";
        outFile << "<body>\n";
    }

    //write each line of the text file to the html file if both html and text file are open
    if (inFile.is_open()){ //checks input file
        while (getline(inFile, inputString)){ //goes line by line
            if(outFile.is_open()){ //checks output file
                outFile << "<p><b>" << inputString << "</b></p>\n"; //adds each line
            }
        }
        if(outFile.is_open()){
            outFile << "<p><b></b><br></p>\n";
        }
    }

    //close and open input to reset back to the top
    inFile.close();
    inFile.open(input);

    if (inFile.is_open()){ //if file is open
        while (getline(inFile, inputString)){ //read whole file
            if (isSentence(inputString)){ //checks if the string is a sentence and translates accordingly
                translateString = myTranslator->translateEnglishSentence(inputString);
            } else{
                translateString = myTranslator->translateEnglishWord(inputString);
            }

            if (outFile.is_open()){
                outFile << "<p><i>" << translateString << "</i><br></p>\n"; //adds the translated string
            }
        }
    }

    if (outFile.is_open()){ //closes up the html body
        outFile << "</body>\n";
        outFile << "</html>\n";
    }

    //closes both input and output files
    inFile.close();
    outFile.close();
}