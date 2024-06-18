#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include "Faculty.h"
#include "LazyBST.h"

class Database {
public:
    Database();
    ~Database();

    void printStudents(TreeNode<Student>* n);
    void printFaculty(TreeNode<Faculty>* n);

    //mostly uses BST methods to work with the student and faculty methods
    void printAllStudents();                                                                                    
    void printAllFaculty();                                                                                     
    bool findStudent(int id);                                                                                   
    bool findFaculty(int id);                                                                                   
    void addStudent(int id, std::string name, std::string level, std::string major, double gpa, int advisorID); 
    void addStudent(Student s);
    void deleteStudent(int id);                                                                                 
    void addFaculty(int id, std::string name, std::string level, std::string department, IntArray *adviseeIDs); 
    void addFaculty(Faculty f);
    void deleteFaculty(int id);                                                                                 
    void changeAdvisor(int studentID, int facultyID);                                                           
    void removeAdvisee(int studentID, int facultyID);                                                           
    void createLogs();
    
    IntArray* getAdviseeIDs(int facultyID);

    int facultyCount();
    int studentCount();
    Student* getStudent(int id);
    Faculty* getFaculty(int id);

    void printAllStudents(ostream& file);
    void printAllFaculty(ostream& file);
private:
    LazyBST<Student> *m_studentTable;
    LazyBST<Faculty> *m_facultyTable;
};

#endif