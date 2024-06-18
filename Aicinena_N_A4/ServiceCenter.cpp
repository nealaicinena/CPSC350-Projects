#include "ServiceCenter.h"
#include <fstream>
#include <sstream>
#include <iostream>

//ServiceCenter constructor.
ServiceCenter::ServiceCenter(){
    m_clockTick = 0;
}

//ServiceCenter overload constructor.
//Parameters: string - File input name.
ServiceCenter::ServiceCenter(std::string inFile){
    m_clockTick = 0;
    m_tickInfo = new TickInfo();
    processFile(inFile);
}

//ServiceCenter destructor - Prints final output to display to terminal.
ServiceCenter::~ServiceCenter(){
    std::string finalString;
    finalString = "Number of students waiting over 10 minutes across all offices: " + std::to_string(getStudentsWaitingOverTen()) + "\n";
    finalString += "Number of windows idle for over 5 minutes across all offices: " + std::to_string(getWindowsIdleOverFive()) + "\n";
    
    delete m_tickInfo;
    delete m_cashier;
    delete m_financial;
    delete m_registrar;
    std::cout << finalString << std::endl;
}

//getStudentsWaitingOverTen method - Returns int of total students waiting over 10 ticks.
int ServiceCenter::getStudentsWaitingOverTen(){
    return m_registrar->getStudentsWaitingOverTen() + m_cashier->getStudentsWaitingOverTen() + m_financial->getStudentsWaitingOverTen();
}

//getWindowsIdleOverFive method - Returns int of total windows idle over 5 ticks.
int ServiceCenter::getWindowsIdleOverFive(){
    return m_registrar->getWindowsIdleOverFive() + m_cashier->getWindowsIdleOverFive() + m_financial->getWindowsIdleOverFive();
}

//serviceCentersSimulation method - Simulates the service center.
void ServiceCenter::serviceCenterSimulation(){
    advanceTick();
    while (m_clockTick != 20){
        advanceTick();
    }
}

//processFile method - Reads the input file.
//Parameters: string inFile - Name of the input file.
void ServiceCenter::processFile(std::string inFile){
    std::ifstream reader;
    std::string line;
    reader.open(inFile);

    int R_windowNum;
    int C_windowNum;
    int F_windowNum;
    int arriveTime;
    int studentNum;
    int lineCount = 1;
    int tmpLineCount;

    while (getline(reader,line)){
        if (line[0] == 'E'){
            break;
        }
        switch(lineCount){
            case 1:
                R_windowNum = stoi(line);
                break;
            case 2:
                C_windowNum = stoi(line);
                break;
            case 3:
                F_windowNum = stoi(line);
                break;
            case 4:
                arriveTime = stoi(line);
                break;
            case 5:
                studentNum = stoi(line);
                break;
            case 6: 
                for (int i = 0; i < studentNum; ++i){
                    Customer* customer = collectStudentInfo(line, arriveTime); //Makes customer.
                    m_tickInfo->addToCustomerQ(customer); //Adds to queue. 

                    if (i != studentNum - 1){
                        getline(reader, line); //Gets line for next student.
                        ++lineCount;
                    }
                }
                break;
            default:
                if (lineCount == 6 + studentNum){ //Line after student wait values.
                    arriveTime = stoi(line);
                } else if (lineCount == 7 + studentNum){
                    tmpLineCount = 7 + studentNum; //Saves line because studentNum gets reassigned.
                    studentNum = stoi(line);
                } else if (lineCount == tmpLineCount + 1){
                    for (int i = 0; i < studentNum; ++i){
                        Customer* customer = collectStudentInfo(line, arriveTime);
                        m_tickInfo->addToCustomerQ(customer);

                        if (i != studentNum - 1){
                            getline(reader, line); //Gets line for next student.
                            ++lineCount;
                        }
                    }
                }
                break;
        }
        ++lineCount;
    }

    makeOffices(R_windowNum, C_windowNum, F_windowNum);
}

//getOfficeChar method.
//Parameter: string value - The input char that signifies the office.
char ServiceCenter::getOfficeChar(std::string value){
    if (value[0] == 'C'){
        return 'C';
    } else if (value[0] == 'R'){
        return 'R';
    } else if (value[0] == 'F'){
        return 'F';
    }
}

//collectStudentInfo method - Returns Customer pointer. Organizes and allocates student info from the input file.
//Parameters: string line, int arriveTime.
Customer* ServiceCenter::collectStudentInfo(std::string line, int arriveTime){
    Customer* customer;
    std::stringstream ss(line);
    std::string value;
    ListQueue<char>* m_officeOrder = new ListQueue<char>();
    ListQueue<int>* m_officeTimes = new ListQueue<int>();
    int valueCount = 1;
    while (ss >> value){
        switch(valueCount){
            case 1:
                m_officeTimes->add(stoi(value));
                break;
            case 2:
                m_officeTimes->add(stoi(value));
                break;
            case 3:
                m_officeTimes->add(stoi(value));
                break;
            case 4:
                m_officeOrder->add(getOfficeChar(value));
                break;
            case 5:
                m_officeOrder->add(getOfficeChar(value));
                break;
            case 6:
                m_officeOrder->add(getOfficeChar(value));
                break;
            default:
                break;
        }
        ++valueCount;
    }

    customer = new Customer(arriveTime, m_officeOrder, m_officeTimes);
    return customer;
}

//moveCustomer method - Moves customer to the correct office.
//Parameters: Customer* customer.
void ServiceCenter::moveCustomer(Customer* customer){
    switch(customer->m_currentOffice){
        case 'C':
            m_cashier->m_officeQueue->add(customer);
            m_cashier->fillWindow();
            break;
        case 'R':
            m_registrar->m_officeQueue->add(customer);
            m_registrar->fillWindow();
            break;
        case 'F':
            m_financial->m_officeQueue->add(customer);
            m_financial->fillWindow();
            break;
        default:
            break;
    }
}

//makeOffices method - Creates offices.
void ServiceCenter::makeOffices(int R_windowNum, int C_windowNum, int F_windowNum){
    m_registrar = new Office('R', R_windowNum); //Each have arrays for number of windows open at each office.
    m_cashier = new Office('C', C_windowNum);
    m_financial = new Office('F', F_windowNum);
}

//advanceTick method - AIncreases tick time, and calls advancesTick.
void ServiceCenter::advanceTick(){
    int customerNum = m_tickInfo->m_customerQueue->size();
    for (int i = 0; i < customerNum; ++i){
        if (m_tickInfo->m_customerQueue->peek()->getArriveTime() == m_clockTick){
            moveCustomer(m_tickInfo->m_customerQueue->remove());
        } 
    }

    if (m_clockTick != 0){
        m_registrar->advanceTick();
        m_cashier->advanceTick();
        m_financial->advanceTick();
    }

    checkToMoveCustomer(m_registrar);
    checkToMoveCustomer(m_cashier);
    checkToMoveCustomer(m_financial);

    ++m_clockTick;
}

//checkToMoveCustomer method - If leavingQueue still has customers, move customer to the next office.
void ServiceCenter::checkToMoveCustomer(Office* office){
    while (!office->m_leavingQueue->isEmpty()){
        moveCustomer(office->m_leavingQueue->remove());
    }
}