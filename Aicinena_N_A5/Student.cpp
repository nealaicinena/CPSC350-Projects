#include "Student.h"
#include <iostream>

//almost copy paste of the faculty class with different member variables
Student::Student() : Student(0) {

}

Student::Student(int id) : Student(id, "", "", "", 0.0, 0) {

}

Student::Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorID) {
    m_id = id;
    m_name = name;
    m_level = level;
    m_major = major;
    m_gpa = gpa;
    m_advisorID = advisorID;
}

Student::~Student() {

}

//comparisons for all ID student values
bool Student::operator==(const Student& s) {
    return m_id == s.m_id;
}

bool Student::operator!=(const Student& s) {
    return m_id != s.m_id;
}

bool Student::operator<(const Student& s) {
    return m_id < s.m_id;
}

bool Student::operator>(const Student& s) {
    return m_id > s.m_id;
}

bool Student::operator<=(const Student& s) {
    return m_id <= s.m_id;
}

bool Student::operator>=(const Student& s) {
    return m_id >= s.m_id;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student ID:  " << s.m_id << std::endl;
    os << "Name:        " << s.m_name << std::endl;
    os << "Level:       " << s.m_level << std::endl;
    os << "Major:       " << s.m_major << std::endl;
    os << "GPA:         " << s.m_gpa << std::endl;
    os << "Advisor ID:  " << s.m_advisorID << std::endl;
    os << std::endl;
    return os;
}