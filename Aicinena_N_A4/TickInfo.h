#ifndef TICKINFO_H
#define TICKINFO_H
#include "ListQueue.h"
#include "Customer.h"

class Customer;

class TickInfo{
    public:
        TickInfo();
        ~TickInfo();

        ListQueue<Customer*>* m_customerQueue;
        
        void tickForward();
        void addToCustomerQ(Customer* customer);
        

};

#endif