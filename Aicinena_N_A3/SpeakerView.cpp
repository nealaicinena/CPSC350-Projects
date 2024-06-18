#include "SpeakerView.h"

SpeakerView::SpeakerView() {
    input = "input.txt";
    lines = 0;
    columns = 1;
    currCol = 0;

    ifstream file(input);
    if(!file.is_open()) {
        throw runtime_error("Error opening file: " + input); //if file cannot open then throw error
    }

    string line;
    while(getline(file, line)) {
        if(lines == 0) { //for the first line...
            for(int i = 0; i < line.size(); ++i) {
                if(line[i] == ' ') { //if char is a space
                    ++columns; //add to columns for each space seperating numbers
                }
            }
        }
        ++lines; //add to the lines
    }
    file.close(); //close files
}

SpeakerView::SpeakerView(string n) {
    input = n;
    lines = 0;
    columns = 1; //start reading column 1
    currCol = 0;

    ifstream file(input);
    if(!file.is_open()) {
        throw runtime_error("Error opening file: " + input); //if file cannot open then throw error
    }

    string line;
    while(getline(file, line)) {
        if(lines == 0) { //for the first line...
            for(int i = 0; i < line.size(); ++i) {
                if(line[i] == ' ') { //if char is a space
                    ++columns; //add to columns for each space seperating numbers
                }
            }
        }
        ++lines; //add to the lines
    }
    file.close(); //close files
}

SpeakerView::~SpeakerView() {

}

string SpeakerView::checkColumns() {
    string output;
    while(currCol < columns) { //iterates through all the columns
        GenStack<double> *myGenStack = new GenStack<double>(lines);
        MonoStack<double> *myMonoStack = new MonoStack<double>(lines, 'd'); //decreasing monostack
        myMonoStack->clear(); //clear stacks to make sure they are empty before we add to them
        myGenStack->clear();

        ifstream file(input);
        if(!file.is_open()) {
            throw runtime_error("Error opening file: " + input);
        }
        string line;  
        while(getline(file, line)) { //read through all the lines
            int currNum = 0; //start at first number
            int index = 0; //index of char in the line
            string number;
            while(currNum < currCol) { //while the number were looking for is less than the column were in (trying to align the number with the column were searching in)
                while(line[index] != ' ') { //while the character is a space
                    ++index; //keep going to the next char
                }
                ++index; //go to the next char
                ++currNum;
            }
            while(line[index] != ' ') { //while we don't encounter a space
                number += line[index]; //add char to the number
                ++index; //go to the next char
            }
            myGenStack->push(stod(number)); //once we have the whole number, convert to double and push to stack
        }
        file.close(); //close file

        for(int i = 0; i < columns + 1; ++i) {
            double result = myGenStack->pop(); //pop the stack and push to monostack to flip the order of the heights    
            myMonoStack->push(result);
        }

        output += "In column " + to_string(currCol) + " there are " + to_string(myMonoStack->getSize()) + " that can see. Their heights are: " + myMonoStack->printStack() + " inches.\n"; //store all the info in the output
        
        ++currCol; //go to the next column
        myMonoStack->clear(); //clear the monostack
        delete myMonoStack; //deallocate memory for both stacks
        delete myGenStack;
    }
    return output; //return output of all the columns height check
        
}