#ifndef OFFICE_H
#define OFFICE_H
#include "Window.h"
#include <string>
#include "ListQueue.h"
#include "Customer.h"

class Customer;
class Window;

class Office{
    public:
        Office();
        Office(char officeType, int windowNum);
        ~Office();

        ListQueue<Customer*>* m_officeQueue;
        ListQueue<Customer*>* m_enteringQueue;
        ListQueue<Customer*>* m_leavingQueue;
        int m_openWindows;
        int m_longestIdleTime;
        int m_longestWaitTime;
        Window** m_windows;

        void advanceTick();     
        void tryToFillWindow();
        void manageOfficeQueue();
        void removeCustomer(Window* window);
        void displayFinalInfo();
        void setLongestTimes(Window* window);
        void fillWindow();

        bool isWindowsEmpty();
        double calculateMeanWaitTime();
        double calculateMeanIdleTime();
        int getStudentsWaitingOverTen();
        int getWindowsIdleOverFive();
    private:
        char m_officeType;
        void handleOpenWindow(Window* window);
        void handleFullWindow(Window* window);
};

#endif