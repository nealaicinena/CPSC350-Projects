#include "Customer.h"
#include <iostream>


//Customer constructor.
Customer::Customer(){
    //Member variables.
    m_arriveTime = 0; //int - The time the customer arrives to the service center.
    m_officeOrder = new ListQueue<char>(); //char list queue - Order that the customer goes to the offices.
    m_officeTimes = new ListQueue<int>(); //int list queue - Times that correspond with the the offices.
    m_currentOffice = m_officeOrder->remove(); //char - Pops the first office that the customer visits.
    m_currentOfficeTime = m_officeTimes->remove(); //int - Pops the time that corresponds with that office.
}

//Customer overload constructor.
//Parameters: int arriveTime, ListQueue<char>* officeOrder, ListQueue<int>* officeTimes.
Customer::Customer(int arriveTime, ListQueue<char>* officeOrder, ListQueue<int>* officeTimes){
    m_arriveTime = arriveTime;
    m_officeOrder = officeOrder;
    m_officeTimes = officeTimes;
    m_currentOffice = m_officeOrder->peek(); //char - Peeks at the first office that the customer visits.
    m_currentOfficeTime = m_officeTimes->peek(); //int - Peeks the time that corresponds with that office.
}

//Customer destructor.
Customer::~Customer(){
    delete m_officeOrder;
    delete m_officeTimes;
}

//getArriveTime method - Returns an int of the the time that the student arrives at the service center.
int Customer::getArriveTime(){
    return m_arriveTime;
}

//addWaitTime method - Increments m_waitTime by one tick.
void Customer::addWaitTime(){
    m_waitTime++;
}

//decreaseOfficeTime method - Decrements m_currentOfficeTime by one tick.
void Customer::decreaseOfficeTime(){
    //If student has visited all the offices and there's no more to visit.
    if (m_officeTimes->isEmpty()){
        return;
    }

    m_currentOfficeTime--;
}

//getWaitTime method - Returns an int of the customer's wait time.
int Customer::getWaitTime(){
    return m_waitTime;
}

//changeCurrentOffice method - Sets customer's new current office and new current office time.
void Customer::changeCurrentOffice(){
    m_officeOrder->remove();
    m_officeTimes->remove();
    if (m_officeOrder == NULL){
        return;
    } else {
        if (m_officeOrder->size() != 0){
            m_currentOffice = m_officeOrder->peek();
            m_currentOfficeTime = m_officeTimes->peek();
        }
    }
}