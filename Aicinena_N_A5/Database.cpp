#include "Database.h"
#include <iostream>

Database::Database() {
    m_studentTable = new LazyBST<Student>();
    m_facultyTable = new LazyBST<Faculty>();
}

Database::~Database() {
    delete m_studentTable;
    delete m_facultyTable;
}

void Database::printAllStudents() {
    m_studentTable->printInOrder();
}

//takes in a file to know which students to be printed
void Database::printAllStudents(ostream& file) {
    m_studentTable->printInOrder(file);
}

void Database::printAllFaculty() {
    m_facultyTable->printInOrder();
}

//takes in a file to know which faculty to be printed
void Database::printAllFaculty(ostream& file) {
    m_facultyTable->printInOrder(file);
}

bool Database::findStudent(int id) {
    return m_studentTable->contains(Student(id)); //searches based off ID number
}

bool Database::findFaculty(int id) {
    return m_facultyTable->contains(Faculty(id));
}

void Database::addStudent(int id, std::string name, std::string level, std::string major, double gpa, int advisorID) { //gets all data as parameters
    
    if (m_studentTable->contains(Student(id))) { //error message incase matching ID
        std::cout << "Student with id " << id << " already exists in the database." << std::endl;
        return;
    }
    m_studentTable->insert(Student(id, name, level, major, gpa, advisorID)); //if no overlap then create and insert new student
} 

void Database::addStudent(Student s) {
    m_studentTable->insert(s);
    
    Faculty* facultyMember = m_facultyTable->get(Faculty(s.m_advisorID));
    if (facultyMember == NULL){
        std::cout << "Faculty member with id " << s.m_advisorID << " does not exist in the database." << std::endl;
        return;
    }

    if(facultyMember->m_adviseeIDs->find(s.m_id) == -1) {
        facultyMember->m_adviseeIDs->add(s.m_id);
    }
}

void Database::deleteStudent(int id) {
    Student* student = getStudent(id);
    if (student == NULL){ //if student does not exist
        std::cout << "Student with id " << id << " does not exist in the database." << std::endl;
        return;
    }
    Faculty* facultyMember = getFaculty(student->m_advisorID);
    if (facultyMember == NULL){
        std::cout << "Faculty member with id " << student->m_advisorID << " does not exist in the database." << std::endl;
        return;
    }
    facultyMember->m_adviseeIDs->remove(id);
}

void Database::addFaculty(int id, std::string name, std::string level, std::string department, IntArray *adviseeIDs){
    m_facultyTable->insert(Faculty(id, name, level, department, adviseeIDs));
}

void Database::addFaculty(Faculty f) {
    
    m_facultyTable->insert(f);

    Faculty *facultyMember = m_facultyTable->get(Faculty(f.m_id));
    if (facultyMember->m_adviseeIDs->size() > 0){
        for (int i = 0; i < facultyMember->m_adviseeIDs->size(); ++i){
            Student* student = m_studentTable->get(Student(facultyMember->m_adviseeIDs->get(i)));
            if (student == NULL){
                continue;
            }

            changeAdvisor(student->m_id, facultyMember->m_id);
        }
    }

}

void Database::deleteFaculty(int id) {
    Faculty* facultyMember = getFaculty(id);

    if (facultyMember == NULL){
        std::cout << "Faculty member with id " << id << " does not exist in the database." << std::endl;
        return;
    }
    if (facultyMember->m_adviseeIDs->size() > 0){
            std::cout << "Reassign advisees to another faculty member." << std::endl;
    }

    m_facultyTable->remove(Faculty(id));

}

void Database::changeAdvisor(int studentID, int facultyID) { //same checks as inserting
    Student* student = getStudent(studentID);
    if (student == NULL){
        std::cout << "Student with id " << studentID << " does not exist in the database." << std::endl;
        return;
    }
    Faculty* facultyMember = getFaculty(facultyID);
    if (facultyMember == NULL){
        std::cout << "Faculty member with id " << facultyID << " does not exist in the database." << std::endl;
        return;
    }
    Faculty* oldAdvisor = getFaculty(student->m_advisorID);
    oldAdvisor->m_adviseeIDs->remove(studentID);

    student->m_advisorID = facultyID;

    if(facultyMember->m_adviseeIDs->find(studentID) == -1){
        facultyMember->m_adviseeIDs->add(studentID);
    }
}

void Database::removeAdvisee(int studentID, int facultyID) {
    Student* student = getStudent(studentID);
    if (student == NULL) {
        std::cout << "Student with id " << studentID << " does not exist in the database." << std::endl;
        return;
    }
    Faculty* facultyMember = getFaculty(facultyID);
    if (facultyMember == NULL) {
        std::cout << "Faculty member with id " << facultyID << " does not exist in the database." << std::endl;
        return;
    }
    facultyMember->m_adviseeIDs->remove(studentID);

}

void Database::createLogs() {

}

int Database::facultyCount() {
    return m_facultyTable->size();
}

int Database::studentCount() {
    return m_studentTable->size();
}

Student* Database::getStudent(int id) {
    return m_studentTable->get(Student(id));
}

Faculty* Database::getFaculty(int id) {
    return m_facultyTable->get(Faculty(id));
}

IntArray* Database::getAdviseeIDs(int facultyID) {
    Faculty* facultyMember = getFaculty(facultyID);
    if (facultyMember == NULL){
        std::cout << "Faculty member with id " << facultyID << " does not exist in the database." << std::endl;
        return NULL;
    }
    return facultyMember->m_adviseeIDs;
}