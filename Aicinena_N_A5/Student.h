#ifndef STUDENT_H
#define STUDENT_H
#include <string>

class Student{
    public:
        Student(); //default constructor
        Student(int id); //overloaded constructor
        Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorID); //overloaded constructor
        ~Student(); //default destructor

        //comparison methods
        bool operator==(const Student& s);
        bool operator!=(const Student& s);
        bool operator<(const Student& s);
        bool operator>(const Student& s);
        bool operator<=(const Student& s);
        bool operator>=(const Student& s);
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
    private:
        int m_id;
        std::string m_name;
        std::string m_level;
        std::string m_major;
        double m_gpa;
        int m_advisorID;

        friend class Database;
};


#endif