#include "Office.h"
#include <iostream>

//Office constructor.
Office::Office(){
    //Member variables.
    m_officeType = ' '; //char - The char that signifies what office it is.
    m_openWindows = 0; //int - Number of windows that the office has.
    m_longestIdleTime = 0; //int - The window with the longest idle time.
    m_longestWaitTime = 0; //int - The window with the longest wait time.
    m_officeQueue = new ListQueue<Customer*>(); //Customer list queue - Customers that are in line for this office.
    m_leavingQueue = new ListQueue<Customer*>(); //Customer list queue - Customers that have finished at this office, enters a leaving queue to be sorted to their next offices.
}

//Office overload constructor.
//Parameters: char officeType, int windows - Number of windows at this office.
Office::Office(char officeType, int windows){
    m_officeType = officeType;
    m_openWindows = windows;
    m_longestIdleTime = 0;
    m_longestWaitTime = 0;
    m_officeQueue = new ListQueue<Customer*>();
    m_leavingQueue = new ListQueue<Customer*>();
    m_windows = new Window*[m_openWindows]; //Array of window pointers.

    //Dynamically allocating an array of windows for this office.
    for (int i = 0; i < m_openWindows; ++i){
        m_windows[i] = new Window(m_officeQueue);
    }
}


//Office destructor. 
Office::~Office(){

    //Final print statement displayed to terminal.
    if (m_officeType == 'C'){
        std::cout << "Cashier's Office: " << std::endl;
    } else if (m_officeType == 'R'){
        std::cout << "Registrar's Office: " << std::endl;
    } else if (m_officeType == 'F'){
        std::cout << "Financial Aid Office: " << std::endl;
    }
    displayFinalInfo();

    delete[] m_windows;
}

//advanceTick method - Handles what happens in an office during a tick.
void Office::advanceTick(){
    tryToFillWindow();
    manageOfficeQueue();
}

//manageOfficeQueue method - Increments wait time for customers in office queue.
void Office::manageOfficeQueue(){
    if (!m_officeQueue->isEmpty()){
        //Add to the wait time of each customer by putting them in queue and then readding them.
        ListQueue<Customer*>* tempQ = new ListQueue<Customer*>();
        while (!m_officeQueue->isEmpty()){
            Customer* customer = m_officeQueue->remove();
            customer->addWaitTime();
            tempQ->add(customer);
        }
        while (!tempQ->isEmpty()){
            Customer* customer = tempQ->remove();
            m_officeQueue->add(customer);
        }
    }
}

//tryTofillWindow method - Handles windows based on if it's open or closed.
void Office::tryToFillWindow(){
    for (int i = 0; i < m_openWindows; ++i){
        if (m_windows[i]->m_isOpen){
            handleOpenWindow(m_windows[i]);
        } else {
            handleFullWindow(m_windows[i]);
        }
    }
}

//fillWindow method - Same as tryToFillWindow method, but it doesn't decrease m_officeTime for the customer in the window.
void Office::fillWindow(){
    for (int i = 0; i < m_openWindows; ++i){
        if (m_windows[i]->m_isOpen){
            handleOpenWindow(m_windows[i]);
        } else {
            return;
        }
    }
}

//handleFullWindow method - Decreases m_officeTime for customer in the window, removes customer if they are done at office.
//Parameters: Window* window - The window pointer that it is dealing with.
void Office::handleFullWindow(Window* window){
    window->customer->decreaseOfficeTime(); //Customer is in there for one less tick.

    if (window->customer->m_currentOfficeTime == 0){ //If thats the customers last tick we remove the customer.
        //Try to get new customer for window.
        if (!m_officeQueue->isEmpty()){
            m_officeQueue->peek()->addWaitTime();
        }
        
        removeCustomer(window);
    }
}

//handleOpenWindow method - Increases idle time if there is no customer waiting in m_officeQueue.
//Parameters: Window* window - The window pointer that it is dealing with.
void Office::handleOpenWindow(Window* window){
    if (!m_officeQueue->isEmpty()){ //If the office queue is empty.
        window->customer = m_officeQueue->remove(); //Put office queue customer in the window.
        window->studentVisiting();
    } else { //But if the office queue has someone in there.
        window->increaseIdleTime(); //But if the entering queue is also empty increase window idle time.
    }
}

//removeCustomer method - Removes customer from the office, adds customer to m_leavingQueue or if no more offices to visit then the customer gets deleted.
void Office::removeCustomer(Window* window){
    //Longest idle time and longest wait time updates.
    setLongestTimes(window);
    window->customer->changeCurrentOffice(); //Changing current office here.

    if (window->customer->m_officeOrder->isEmpty()){ //OfficeOrder is empty.
        delete window->customer;
    } else { //Office order is not empty add to leaving queue.
        m_leavingQueue->add(window->customer);
    }

    window->studentLeaving();
    window->getNewCustomer();
}

//setLongestTimes method.
//Parameters: Window* window - The window pointer that it is dealing with.
void Office::setLongestTimes(Window* window){
    if (m_longestIdleTime < window->m_idleTime){
        m_longestIdleTime = window->m_idleTime;
    }
    if (m_longestWaitTime < window->customer->getWaitTime()){
        m_longestWaitTime = window->customer->getWaitTime();
    }
}

//isWindowsEmpty method - Returns bool checking if window is empty or not.
bool Office::isWindowsEmpty(){
    for (int i = 0; i < m_openWindows; ++i){
        if (m_windows[i]->m_isOpen){
            return false;
        }
    }
    return true;
}

//displayFinalInfo method.
void Office::displayFinalInfo(){
    std::cout << "Mean student wait time: " << calculateMeanWaitTime() << " tick(s)" << std::endl;
    std::cout << "Mean window idle time: " << calculateMeanIdleTime() << " tick(s)" << std::endl;
    std::cout << "Longest student wait time: " << m_longestWaitTime << " tick(s)" << std::endl;
    std::cout << "Longest window idle time: " << m_longestIdleTime << " tick(s)" << std::endl;
}

//calculateMeanIdleTime method - Returns double of the mean idle time for all windows in an office.
double Office::calculateMeanIdleTime(){
    double totalIdleTime = 0;
    for (int i = 0; i < m_openWindows; ++i){
        totalIdleTime += m_windows[i]->m_idleTime;
    }
    return totalIdleTime / m_openWindows;
}

//calculateMeanWaitTime method - Returns double of the mean wait time for all the windows in an office.
double Office::calculateMeanWaitTime(){
    double totalWaitTime = 0;
    int totalCustomersSeen = 0;
    for (int i = 0; i < m_openWindows; ++i){
        totalWaitTime += m_windows[i]->m_totalWaitTime;
        totalCustomersSeen += m_windows[i]->m_customersSeen;
    }
    return totalWaitTime / totalCustomersSeen;
}

//getStudentsWaitingOverTen method - Returns int of the number of students that have waited for over 10 ticks for this office.
int Office::getStudentsWaitingOverTen(){
    int totalStudentsWaitingOverTen = 0;
    for (int i = 0; i < m_openWindows; ++i){
        totalStudentsWaitingOverTen += m_windows[i]->m_studentsWaitingOverTen;
    }
    return totalStudentsWaitingOverTen;
}

//getWindowsIdleOverFive - Returns int of the number of windows that have been idle for over 5 ticks for this office.
int Office::getWindowsIdleOverFive(){
    int totalWindows = 0;
    for (int i = 0; i < m_openWindows; ++i){
        if (m_windows[i]->m_idleTime > 5){
            totalWindows++;
        }
    }
    return totalWindows;
}
