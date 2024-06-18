#include "DatabaseSystem.h"
#include "IntArray.h"

#include <fstream>

DatabaseSystem::DatabaseSystem() {
    m_database = new Database();
}

DatabaseSystem::~DatabaseSystem() {
    delete m_database;
}

// should be called at the start to present the options
void DatabaseSystem::printMenu() {
    std::cout << "\n";
    std::cout << "1.   Print all students and their information (sorted by ascending id #)" << std::endl;
    std::cout << "2.   Print all faculty and their information (sorted by ascending id #)" << std::endl;
    std::cout << "3.   Find and display student information given the student id" << std::endl;
    std::cout << "4.   Find and display faculty information given the faculty id" << std::endl;
    std::cout << "5.   Add a new student" << std::endl;
    std::cout << "6.   Delete a student given the id" << std::endl;
    std::cout << "7.   Add a new faculty member" << std::endl;
    std::cout << "8.   Delete a faculty member given the id." << std::endl;
    std::cout << "9.   Change a student's advisor given the student id and the new faculty id." << std::endl;
    std::cout << "10.  Remove an advisee from a faculty member given the ids" << std::endl;
    std::cout << "11.  Exit" << std::endl;
}

//used for all input for all options
int DatabaseSystem::getIntInput(int lowerBound, int upperBound) {
    int input;

    while(!(std::cin >> input) || input < lowerBound || input > upperBound) { // error message to comply with bounds
        std::cout << "Invalid input. Please enter a number between " << lowerBound << " and " << upperBound << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    return input;
}

//used for decimal number inputs
double DatabaseSystem::getDoubleInput(double lowerBound, double upperBound){
    double input = -1;

    while(!(std::cin >> input) || input < lowerBound || input > upperBound) {
        std::cout << "Invalid input. Please enter a number between " << lowerBound << " and " << upperBound << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return input;
}

std::string DatabaseSystem::getStringInput() {
    std::string input;

    std::getline(std::cin, input);

    return input;
}

std::string DatabaseSystem::getStringInput(std::string *options) {  
    std::string input;
    std::getline(std::cin, input);

    return input;
}

IntArray* DatabaseSystem::makeStudentIDList() {
    std::cout << "Enter the student ids, enter a '-1' when done: ";
    IntArray *list = new IntArray();

    int input;
    do{
        input = getIntInput(-1, 2147483647);
        if (input != -1) {
            if (!(m_database->findStudent(input))) {
                std::cout << "Student with id " << input << " does not exist in the database. Please choose an existing student." << endl;
                continue;
            }
            if (list->find(input) != -1) {
                std::cout << "Student with id " << input << " is already in the list. Please choose a different student." << endl;
                continue;
            }

            list->add(input);
        }
    } while (input != -1);

    return list;
}

Student DatabaseSystem::makeNewStudent() { //asks questions for all the input needed
    std::cout << "Enter the student id:           ";
    int id = getIntInput(0, 2147483647);
    while (m_database->findStudent(id)){
        std::cout << "Student with id " << id << " already exists in the database. Please choose a different id." << std::endl;
        id = getIntInput(0, 2147483647);
    }
    std::cout << "Enter the student name:         ";
    std::string name = getStringInput();
    std::cout << "Enter the student level:        ";
    std::string level = getStringInput();
    std::cout << "Enter the student major:        ";
    std::string major = getStringInput();
    std::cout << "Enter the student gpa:          ";
    double gpa = getDoubleInput(0.0, 5.0);
    std::cout << "Enter the student's advisor id: ";
    int advisorID = getIntInput(0, 2147483647);

    while (!(m_database->findFaculty(advisorID))) {
        std::cout << "Faculty member with id " << advisorID << " does not exist in the database. Please choose an existing faculty member." << std::endl;
        advisorID = getIntInput(0, 2147483647);
    }

    return Student(id, name, level, major, gpa, advisorID); //creates the student once we have all the data

}

Faculty DatabaseSystem::makeNewFaculty() { //similar style to student. asks questions and takes answers for creating a faculty
    std::cout << "Enter the faculty id:         ";
    int id = getIntInput(0, 2147483647);           
    std::cout << "Enter the faculty name:       ";
    std::string name = getStringInput();
    std::cout << "Enter the faculty level:      ";
    std::string level = getStringInput();
    std::cout << "Enter the faculty department: ";
    std::string department = getStringInput();
    std::cout << "Do you want to enter the faculty advisee ids now?: \n1. Yes\n2. No\n";
    int input = getIntInput(1, 2);
    if (input == 1) {
        std::cout << "Enter the faculty advisee ids: ";
        IntArray *adviseeIDs = makeStudentIDList();
        return Faculty(id, name, level, department, adviseeIDs);
    }
    return Faculty(id, name, level, department, NULL);
}

void DatabaseSystem::printStudent(int id) {
    if (m_database->findStudent(id)) {
        std::cout << *(m_database->getStudent(id)) << std::endl; //prints out student with the corresponding ID
    } else {
        std::cout << "Student with id " << id << " does not exist in the database." << std::endl;
    }
}

void DatabaseSystem::printFaculty(int id) {
    if(m_database->findFaculty(id)) {
        std::cout << *(m_database->getFaculty(id)) << std::endl; //prints out the faculty with the corresponding ID
    } else{
        std::cout << "Faculty member with id " << id << " does not exist in the database." << std::endl;
    }
}

void DatabaseSystem::removeAdvisees(int facultyID) {
    IntArray *adviseeIDs = m_database->getAdviseeIDs(facultyID); //gets advisee first to know what to remove
    if (adviseeIDs != NULL) {
        if (adviseeIDs->size() == 0) {
            return;
        }
        for (int i = 0; i < adviseeIDs->size(); ++i) {
            std::cout << "Enter new advisor for student " << adviseeIDs->get(i) << ": "; //must have the corresponding student to remove with the advisor
            m_database->changeAdvisor(adviseeIDs->get(i), getIntInput(0, 2147483647)); 
        }
    }
}

void DatabaseSystem::createLog() {
    std::ofstream logFile;
    logFile.open("runLog.txt", std::ofstream::out | std::ofstream::trunc); //open file for reading

    logFile << "All students:\n";
    m_database->printAllStudents(logFile); //prints log of all the students, stored in the database (tree)

    logFile << "------------------------------------\n\n";

    logFile << "All faculty:\n";
    m_database->printAllFaculty(logFile); //prints log of all the faculty, stored in the database (tree)

    logFile.close(); //close file
}

int DatabaseSystem::getMenuInput() {
    int input = getIntInput(1, 11); //range of what to take in (can only be between 1-11)
    int studentID;
    int facultyID;
    int newFacultyID;

    //case for all the options
    switch(input) {
        case 1:
            m_database->printAllStudents();
            break;
        case 2:
            m_database->printAllFaculty();
            break;
        case 3:
            std::cout << "Enter the student id: ";
            printStudent(getIntInput(0, 2147483647));
            break;
        case 4: 
            std::cout << "Enter the faculty id: ";
            printFaculty(getIntInput(0, 2147483647));
            break;
        case 5:
            if (m_database->facultyCount() == 0){
                std::cout << "There are no faculty members in the database. Please add a faculty member before adding a student." << std::endl;
                break;
            }
            m_database->addStudent(makeNewStudent());
            break;
        case 6:
            std::cout << "Enter the student id: ";
            m_database->deleteStudent(getIntInput(0, 2147483647));
            break;
        case 7:
            m_database->addFaculty(makeNewFaculty());
            break;
        case 8:
            std::cout << "Enter the faculty id: ";
            facultyID = getIntInput(0, 2147483647);
            removeAdvisees(facultyID);
            m_database->deleteFaculty(facultyID);
            break;
        case 9:
            std::cout << "Enter the student id: ";
            studentID = getIntInput(0, 2147483647);
            std::cout << "Enter the faculty id: ";
            facultyID = getIntInput(0, 2147483647);
            m_database->changeAdvisor(studentID, facultyID);
            break;
        case 10:
            std::cout << "Enter the student id: ";
            studentID = getIntInput(0, 2147483647);
            while (!(m_database->findStudent(studentID))) {
                std::cout << "Student with id " << studentID << " does not exist in the database. Please choose an existing student." << endl;
                studentID = getIntInput(0, 2147483647);
            }
            std::cout << "Enter the faculty id: ";
            facultyID = getIntInput(0, 2147483647);
            while (!(m_database->findFaculty(facultyID))) {
                std::cout << "Faculty member with id " << facultyID << " does not exist in the database. Please choose an existing faculty member." << endl;
                facultyID = getIntInput(0, 2147483647);
            }
            std::cout << "Enter the students new faculty advisor's id: ";
            newFacultyID = getIntInput(0, 2147483647);
            while (!(m_database->findFaculty(newFacultyID))) {
                std::cout << "Faculty member with id " << newFacultyID << " does not exist in the database. Please choose an existing faculty member." << endl;
                newFacultyID = getIntInput(0, 2147483647);
            }
            m_database->changeAdvisor(studentID, newFacultyID);
            break;
        case 11: 
            std::cout << "Exiting program." << std::endl;
            createLog();
            return 11;
            break;
        default:
            std::cout << "Invalid selection.\n"; //if we get input that is not in range then there is no task to perform
            break;
    }
    return input;
}

void DatabaseSystem::run() { //simulates the database system by taking in input until 11 is taken as input
    int input = 0;
    while(input != 11) {
        printMenu(); //prints menu everytime we go around another turn
        input = getMenuInput(); //input value will be whatever option pressed
    }
}