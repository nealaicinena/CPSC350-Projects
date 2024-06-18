#ifndef SERVICECENTER_H
#define SERVICECENTER_H
#include <string>
#include "Office.h"
#include "TickInfo.h"
#include "Customer.h"
#include "Office.h"

class Office;
class TickInfo;

class ServiceCenter{
    public:
        ServiceCenter();
        ServiceCenter(std::string inFile);
        ~ServiceCenter();

        int m_clockTick; //global variable for clock ticks
        
        void serviceCenterSimulation();
        void moveCustomer(Customer* customer);
        void enterOffice(Customer* customer, char officeChar, int time);
        void makeOffices(int R_windowNum, int C_windowNum, int F_windowNum);
        void advanceTick();
        void checkToMoveCustomer(Office* office);
    private:
        TickInfo* m_tickInfo;
        Office* m_registrar;
        Office* m_cashier;
        Office* m_financial;
        Customer* collectStudentInfo(std::string line, int arriveTime);     
        
        void processFile(std::string);

        bool isGameOver();
        int getStudentsWaitingOverTen();
        int getWindowsIdleOverFive();
        char getOfficeChar(std::string value);
         
};

#endif