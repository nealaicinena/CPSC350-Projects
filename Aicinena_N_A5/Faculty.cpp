#include "Faculty.h"
#include <iostream>

Faculty::Faculty() : Faculty(0) {

}

Faculty::Faculty(int id) : Faculty(id,"","","",NULL) {
    //default empty faculty with basic ID input
}

Faculty::Faculty(int id, std::string name, std::string level, std::string department, IntArray *adviseeIDs) {
    //overloaded and takes in all information
    m_id = id;
    m_name = name;
    m_level = level;
    m_department = department;
    if (adviseeIDs == NULL){ //if ID array is empty then make a new one
        m_adviseeIDs = new IntArray();
    } else {
    m_adviseeIDs = adviseeIDs; //otherwise just set member variable to parameter
    }
}

Faculty::~Faculty() {

}

// all mathmatical comparisons between ID available and simplified through methods
bool Faculty::operator==(const Faculty& f) {
    return (m_id == f.m_id);
}

bool Faculty::operator!=(const Faculty& f) {
    return (m_id != f.m_id);
}

bool Faculty::operator<(const Faculty& f) {
    return (m_id < f.m_id);
}

bool Faculty::operator>(const Faculty& f) {
    return (m_id > f.m_id);
}

bool Faculty::operator<=(const Faculty& f) {
    return (m_id <= f.m_id);
}

bool Faculty::operator>=(const Faculty& f) {
    return (m_id >= f.m_id);
}

//used to display all the information in the file output
std::ostream& operator<<(std::ostream& os, const Faculty& f) {
    os << "Faculty ID:  " << f.m_id << std::endl;
    os << "Name:        " << f.m_name << std::endl;
    os << "Level:       " << f.m_level << std::endl;
    os << "Department:  " << f.m_department << std::endl;
    os << "Advisee IDs: ";
    if(f.m_adviseeIDs == NULL) {
        os << "None" << std::endl << std::endl; //if there is nothing to currently display then just show that it is empty with "none"
        return os;
    }
    os << f.m_adviseeIDs->toString() << std::endl;
    return os;
}