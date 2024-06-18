#ifndef GENSTACK_H
#define GENSTACK_H

#include<iostream>
#include<exception>
using namespace std;

template <class T> //template class
class GenStack{
    public:
        GenStack(); //default constructor
        GenStack(int mSize); //overloaded constructor
        ~GenStack();

        //core functions
        void push(T data);
        T pop();
        T peek(); //aka top()

        //aux functions
        bool isEmpty();
        bool isFull();
        unsigned int getSize();
        string printStack(); //prints the entire stack
        void clear();
        
    private:
        T *myArray;
        int top;
        unsigned int mSize;

};

template <class T>
GenStack<T>::GenStack() { //default stack
    mSize = 64;
    top = -1;
    myArray = new T[mSize];
}

template <class T>
GenStack<T>::GenStack(int maxSize){
    mSize = maxSize;
    top = -1;
    myArray = new T[mSize];
}

template <class T>
GenStack<T>::~GenStack() {
    delete[] myArray; //deletes array
}

template <class T>
void GenStack<T>::push(T data) {
    if(isFull()) {
        T *temp = new T[2*mSize]; //creates array twice the size
        for(int i = 0; i < mSize; ++i) {
            temp[i] = myArray[i]; //copy data from old array to new array
        }
        mSize *= 2;
        delete[] myArray;
        myArray = temp;
    }
    myArray[++top] = data;
}

template <class T>
T GenStack<T>::pop() {
    if(isEmpty()) {
        throw runtime_error("stack is empty, nothing to peek");
    } else {
        return myArray[top--]; //returns top element and lowers the top
    }
}

template <class T>
T GenStack<T>::peek() {
    if(isEmpty()) {
        throw runtime_error("stack is empty, nothing to peek");
    }
    return myArray[top]; //returns top without decreasing it
}

template <class T>
bool GenStack<T>::isFull() {
    return (top == mSize - 1); //return true if size is top
}

template <class T>
bool GenStack<T>::isEmpty() {
    return (top == -1); //true if top is -1
}

template <class T>
unsigned int GenStack<T>::getSize() {  
    return top + 1;
}

template <class T>
void GenStack<T>::clear() {
    for(int i = 0; i < mSize; ++i) {
        myArray[i] = 0; //sets every element to 0
    }
}

template <class T>
string GenStack<T>::printStack() {
    string output;
    for(int i = 0; i < mSize; ++i) {
        double number = myArray[i];
        if(number != 0) {
            string height = to_string(number); //convert double to string
            height = height.substr(0, height.size() - 4); //removes extra zeros that arrise with to_string method
            output += height + ", "; //seperates numbers
        }
    }
    output = output.substr(0, output.size() - 2); //removes extra trailing comma
    return output; //returns all values
}
#endif