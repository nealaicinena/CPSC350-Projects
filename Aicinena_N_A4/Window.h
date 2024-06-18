#ifndef WINDOW_H
#define WINDOW_H
#include "Customer.h"
#include "ListQueue.h"

class Customer;

class Window{
    public:
        Window();
        Window(ListQueue<Customer*>* &officeQ);
        ~Window();

        ListQueue<Customer*>* m_officeQueue;
        Customer* customer;

        bool m_isOpen;
        int m_studentsWaitingOverTen;
        int m_totalWaitTime;
        int m_customersSeen;
        int m_idleTime;

        void studentVisiting();
        void studentLeaving();
        void increaseIdleTime();
        void getNewCustomer();   
};

#endif