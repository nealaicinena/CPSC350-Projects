#include "IntArray.h"
#include <iostream>


IntArray::IntArray() : IntArray(10) {

}

IntArray::IntArray(int initialSize) {
    m_array = new int[initialSize];
    m_maxSize = initialSize;
    m_size = 0;
}

IntArray::~IntArray() {
    delete[] m_array;
}

int IntArray::size() {
    return m_size;
}

void IntArray::add(int value) {
    if(m_size >= m_maxSize) { //if we need to increase the array then double it
        m_maxSize *= 2;
        int *newArray = new int[m_maxSize];
        for(int i = 0; i < m_size; ++i) { 
            newArray[i] = m_array[i];
        }
        delete[] m_array;
        m_array = newArray;
    }
    m_array[m_size] = value; 
    ++m_size;
}

void IntArray::remove(int value) {
    int index = find(value);   
    if(index == -1) { //cannot remove negative index
        return;
    }
    for(int i = index; i < m_size - 1; ++i) {
        m_array[i] = m_array[i + 1];
    }
    --m_size;
}

int IntArray::find(int value) { //simple search that iterates through the array to find the value
    for(int i = 0; i < m_size; ++i) {
        if(m_array[i] == value) {
            return i;
        }
    }
    return -1; //return -1 if not found
}

int IntArray::get(int index) {
    if(index < 0 || index >= m_size) {
        std::cout << "Index out of bounds." << std::endl;
        return -1;
    }
    return m_array[index];
}

void IntArray::print() { //prints all the values to the array
    for(int i = 0; i < m_size; ++i) {
        std::cout << m_array[i];
        if(i != m_size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

std::string IntArray::toString() {
    std::string output = "";
    for(int i = 0; i < m_size; ++i) {
        output += std::to_string(m_array[i]);
        if(i != m_size - 1) {
            output += ", ";
        }
    }
    return output;
}