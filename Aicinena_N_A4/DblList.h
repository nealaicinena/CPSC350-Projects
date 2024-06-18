#ifndef DBLList_H
#define DBLLIST_H
#include "ListNode.h"

template<typename T> 
class DblList{
    public:
        DblList();
        ~DblList();
        int size(); //how many elements are in my linked list

        void addFront(T data);
        void addBack(T data);
        void add(int pos, T data);

        T removeFront();
        T removeBack();
        T remove(int pos);

        T get(int pos);

        bool isEmpty();

    private:
        private:
        ListNode<T>* m_front;
        ListNode<T>* m_back;
        int m_size;
};

template<typename T>
DblList<T>::DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template<typename T>
DblList<T>::~DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template<typename T>
int DblList<T>::size(){
    return m_size;
}

template<typename T>
bool DblList<T>::isEmpty(){
    return (m_size == 0);
}

template<typename T>
void DblList<T>::addFront(T data){
    ListNode<T>* newNode = new ListNode<T>(data);
    // set newNode's prev pointer to NULL (done in constructor)
    if (!isEmpty()){
        newNode->m_next = m_front;
        m_front->m_prev = newNode;
    } else{
        m_back = newNode;
    }
    m_front = newNode;
    ++m_size;

}

template<typename T>
void DblList<T>::addBack(T data){
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!isEmpty()){
        newNode->m_prev = m_back;       // set newNode's previous to oldBack
        m_back->m_next = newNode;       // set oldBack's next to newNode
    } else {
        m_front = newNode;
    }
    m_back = newNode;
    ++m_size;
}

template<typename T>
void DblList<T>::add(int pos, T data){
    if (isEmpty()){
        addFront(data);
    } else if (pos <= 0){
        addFront(data);
    } else if (pos >= size){
        addBack(data);
    } else{
        ListNode<T>* current = m_front;     // start at front
        int cPos = 0;
        while (cPos != pos){            // while current position is not equal to position
            current = current->m_next;  // current is the next node
            cPos++;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        current->m_prev->m_next = newNode;      //current's previous's next is new node
        newNode->m_prev = current->m_prev;      //current's previous is new node's previous
        current->m_prev = newNode;              //current's previous is set to new node
        newNode->m_next = current;              //current becomes new node's next
        ++m_size;
    }
}

template<typename T>
T DblList<T>::removeFront(){
    // make sure list is not empty
    T data = m_front->m_data;       // getting front's data before deleting
    if (m_size == 1){
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    } else{
        ListNode<T>* currFront = m_front;
        m_front = m_front->m_next;
        m_front->m_prev = NULL;
        delete currFront;
    }
    --m_size;
    return data;
}

template <typename T>
T DblList<T>::removeBack(){
    T data = m_back->m_data;
    if (m_size == 1){
        delete m_back;
        m_front = NULL;
        m_back = NULL;
    } else{
        ListNode<T>* currBack = m_back;
        m_back = m_back->m_prev;
        m_back->m_next = NULL;
        delete currBack;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::remove(int pos){
    T data;
    if (pos <= 0){
        data = removeFront();
    } else if (pos >= m_size - 1){
        data = removeBack();
    } else{
        ListNode<T>* current = m_front;
        int cPos = 0;
        while (cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        data = current->m_data;
        current->m_prev->m_next = current->m_next;      //current's previous's next is current's next
        current->m_next->m_prev = current->m_prev;      //current's next's previous is current's previous
        delete current;              
        --m_size;
    }
    return data;
}

template<typename T>
T DblList<T>::get(int pos){
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos){
        current = current->m_next;
        ++cPos;
    }
    return current->m_data;
}

#endif