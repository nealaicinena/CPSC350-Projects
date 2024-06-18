#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Office.h"
#include "ServiceCenter.h"
#include "ListQueue.h"

class Customer{
    public:
        Customer();
        Customer(int arriveTime, ListQueue<char>* officeOrder, ListQueue<int>* officeTimes);
        ~Customer();

        ListQueue<int>* m_officeTimes;   // needs to be decreased for each advance tick
        ListQueue<char>* m_officeOrder;
        char m_currentOffice;
        int m_currentOfficeTime;

        void changeCurrentOffice();
        void addWaitTime();
        void decreaseOfficeTime();

        int getArriveTime();  
        int getWaitTime();
        
    private:
        int m_arriveTime;
        int m_waitTime;  
}; 

#endif