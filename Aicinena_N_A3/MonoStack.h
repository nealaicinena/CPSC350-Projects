#ifndef MONOSTACK_H
#define MONOSTACK_H

#include<iostream>
#include<exception>
#include "GenStack.h"
using namespace std;

template <class T> //template class
class MonoStack{
    public:
        MonoStack(); //default constructor
        MonoStack(int mSize, char o); //overloaded constructor
        ~MonoStack(); //destructor

        //core functions
        void push(T data);
        T pop();
        T peek(); //aka top()

        //aux functions
        void clear(); //clears stack
        bool isEmpty();
        bool isFull();
        bool isIncreasing(); //returns true if stack is increasing
        unsigned int getSize();
        string printStack(); //prints the stack

    private:
        GenStack<T> *myGenStack; //uses genstack in the monostack
        unsigned int mSize;
        bool increasing; //true if stack is increasing
};

template <class T>
MonoStack<T>::MonoStack() { //default stack size 64
    mSize = 64;
    increasing = true; //default increasing
    myGenStack = new GenStack<T>(mSize); //creates genstack of that size
}

template <class T>
MonoStack<T>::MonoStack(int maxSize, char o){
    mSize = maxSize;
    if(o == 'i') //increasing if char is i
        increasing = true;
    else if (o == 'd') //decreasing if char is d
        increasing = false;
    myGenStack = new GenStack<T>(mSize); //creates new stack of size
}

template <class T>
MonoStack<T>::~MonoStack() {
    delete myGenStack; //deletes the genstack
}

template <class T>
void MonoStack<T>::push(T data) {
    GenStack<T> *temp = new GenStack<T>(mSize); //creates temporary stack to hold the numbers we want
    if(increasing) { //if increasing then order in increasing order
        while (!myGenStack->isEmpty()) { //while theres still values in the stack
            T curr = myGenStack->pop(); //temp for current value
            if(curr > data) { //if current is greater than or equal to then push
                temp->push(curr);
            } else {
                myGenStack->push(curr); // Push back if greater than 'data'
                break; // Exit the loop
            }
        }
        myGenStack->push(data); //finally push data to the stack
    } else { //order in decreasing order
        while (!myGenStack->isEmpty()) { //while theres still values in the stack
            T curr = myGenStack->pop(); //temp for current value
            if(curr < data) { //if value is less than data
                temp->push(curr);
            } else {
                myGenStack->push(curr); // Push back if smaller than 'data'
                break; // Exit the loop
            }
        }
        myGenStack->push(data); //finally push data
    }
    delete temp; //delete the temporary stack
}

template <class T>
T MonoStack<T>::pop() {
    return myGenStack->pop(); //pop last element
}

template <class T>
T MonoStack<T>::peek() {
    return myGenStack->peek(); //checks last element
}

template <class T>
bool MonoStack<T>::isFull() {
    return myGenStack->isFull(); //true if the stack is full
}

template <class T>
bool MonoStack<T>::isEmpty() {
    return myGenStack->isEmpty(); //true if the stack is empty
}

template <class T>
unsigned int MonoStack<T>::getSize() {  
    return myGenStack->getSize(); //returns size of stack
}

template <class T>
bool MonoStack<T>::isIncreasing() {
    return increasing; //returns true if stack is increasing
}

template <class T>
void MonoStack<T>::clear() {
    myGenStack->clear(); //clears the genstack
}

template <class T>
string MonoStack<T>::printStack() {
    return myGenStack->printStack(); //prints the stack
}

#endif