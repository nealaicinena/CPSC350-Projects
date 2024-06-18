#ifndef DATABASESYSTEM_H
#define DATABASESYSTEM_H

#include <iostream>
#include <string>
#include "Database.h"

class DatabaseSystem {
    public:
        DatabaseSystem();
        ~DatabaseSystem();

        int getMenuInput();
        int getIntInput(int lowerBound, int upperBound);
        double getDoubleInput(double lowerBound, double upperBound);
        std::string getStringInput();
        std::string getStringInput(std::string *options);
        IntArray* makeStudentIDList();
        Student makeNewStudent();
        Faculty makeNewFaculty();

        void printStudent(int id);
        void printFaculty(int id);

        //methods used for running and simulating the database
        void createLog();
        void printMenu();
        void run();

        int facultyCount();
        int studentCount();
    private:
        Database *m_database;
        void removeAdvisees(int facultyID);

};

#endif