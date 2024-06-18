#include "TickInfo.h"

//TickInfo constructor.
TickInfo::TickInfo(){
    m_customerQueue = new ListQueue<Customer*>();
}

//TickInfo destructor.
TickInfo::~TickInfo(){
    delete m_customerQueue;
}

//addToCustomerQ method.
//Parameters: Customer* c.
void TickInfo::addToCustomerQ(Customer* c){
    m_customerQueue->add(c);
}