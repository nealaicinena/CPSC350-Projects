#ifndef INTARRAY_H
#define INTARRAY_H
#include <string>


class IntArray {             
    public:
        IntArray(); //default constructor
        IntArray(int size); //overloaded constructor
        ~IntArray(); //destructor

        int size();                    

        //used to navigate
        void add(int value);           
        void remove(int value);         
        int find(int value);            
        int get(int index);            
        void print();                  
        std::string toString();   
    private:
        int *m_array;                   
        int m_size;                    
        int m_maxSize;          
};

#endif