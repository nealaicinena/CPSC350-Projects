#include "Window.h"
#include <iostream>

//Window constructor.
Window::Window(){
    m_customersSeen = 0; //int - Number of customers seen by a window.
    m_totalWaitTime = 0; //int - Total wait of all customers at that window.
    m_idleTime = 0; //int - Idle time of that window.
    m_isOpen = true; //bool - Checks if window is open.
    m_studentsWaitingOverTen = 0; //int - Number of students waiting for over 10 ticks.
    customer = nullptr; //Customer pointer - Set to null at first.
}

//Window overload constructor.
//Parameters: ListQueue<Customer*>* &officeQ.
Window::Window(ListQueue<Customer*>* &officeQ){
    m_customersSeen = 0;
    m_totalWaitTime = 0;
    m_idleTime = 0;
    m_officeQueue = officeQ;
    m_isOpen = true;
    m_studentsWaitingOverTen = 0;
    customer = nullptr;
}

//Window destructor.
Window::~Window(){}

//studentVisiting method.
void Window::studentVisiting(){
    m_isOpen = false;
}

//studentLeaving method.
void Window::studentLeaving(){
    m_isOpen = true;
}

//increasIdleTime method.
void Window::increaseIdleTime(){
    ++m_idleTime;
}

//getNewCustomer method.
void Window::getNewCustomer(){
    ++m_customersSeen;
    m_totalWaitTime += customer->getWaitTime();
    
    if (customer->getWaitTime() > 10){
        ++m_studentsWaitingOverTen;
    }

    if (m_officeQueue->isEmpty()){
        customer = nullptr;
    } else{
        customer = m_officeQueue->remove();
        studentVisiting();
    }
}