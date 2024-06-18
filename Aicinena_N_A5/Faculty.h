#ifndef FACULTY_H
#define FACULTY_H

#include "IntArray.h"

#include <string>

class Faculty {
    public:
        Faculty();
        Faculty(int id);
        Faculty(int id, std::string name, std::string level, std::string department, IntArray *adviseeIDs);
        ~Faculty(); //default destructor

        //all comparisons between faculty
        bool operator==(const Faculty& f);
        bool operator!=(const Faculty& f);
        bool operator<(const Faculty& f);
        bool operator>(const Faculty& f);
        bool operator<=(const Faculty& f);
        bool operator>=(const Faculty& f);
        
        friend std::ostream& operator<<(std::ostream& os, const Faculty& f);
    private:
        int m_id;
        std::string m_name;
        std::string m_level;
        std::string m_department;
        IntArray *m_adviseeIDs;

        friend class Database;
};

#endif