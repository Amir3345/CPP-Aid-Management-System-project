/*************************************************************************************

*

* Student Name :Amir Hossein Behzad

* Student ID  :144725223

* Course/Section: OOP244/NBB 2237

*

* I have received help from the following student(s) or website(s).

* For each student, provide their name and course section code:

*

* List any websites or AI tools you used to assist:
   i coding for geeks c++ coureses so i get most of my coding references from there
*
* List the functions/parts that you received help with:
   coded every function by myself other than the codes given in github or by the proffser
*x

* Other than the functions/parts written above, I have done all the coding by myself and

* only copied the code that my professor provided to complete my workshops and assignments.

*

**************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS 
#include <cstring>
#include <iostream>
#include <limits>
#include "Utils.h"
#include "Status.h"

namespace sdds {

    // Default constructor
    Status::Status() : m_state(nullptr), m_code(0) {}

    Status::Status(const char* desc, int code) {
        // Check if desc is not null before allocating memory
        if (desc != nullptr) {
            m_state = new char[strlen(desc) + 1];
            strcpy(m_state, desc);
        }
        else
        {
            m_state = nullptr;
        }
    }

    //copy constturcotor
    Status::Status(const Status& s) {
        *this = s;
    }


    // Assignment operator
    Status& Status::operator=(const Status& s) {
        if (this != &s) {

            // If s.m_state is not null, allocate memory and copy
            if (s.m_state != nullptr) {
                m_state = new char[strlen(s.m_state) + 1];
                strcpy(m_state, s.m_state);
            }

            m_code = s.m_code;
        }

        return *this;
    }


    // Destructor
    Status::~Status() {
        if (m_code != 0) {
            m_code = 0;
        }
        // Check if m_state is not null before deleting
        if (m_state != nullptr) {
            delete[] m_state;
            m_state = nullptr;
        }
    }

    // Assignment operator for setting the status code
    Status& Status::operator=(int sCode) {
        m_code = sCode;
        return *this;
    }

    // Assignment operator for setting the status state
    Status& Status::operator=(const char* state) {
        // Check if m_state is not null before deleting
        if (m_state != nullptr) {
            delete[] m_state;
            m_state = nullptr;
        }
        // Allocate memory and copy the state
        m_state = new char[strlen(state) + 1];
        strcpy(m_state, state);
        return *this;
    }

    // Conversion operator to int
    Status::operator int() const {
        return this->m_code;
    }

    // Conversion operator to const char*
    Status::operator const char* () const {
        return this->m_state;
    }

    // Conversion operator to bool
    Status::operator bool() const {
        return (this->m_state == nullptr);
    }

    // Clear function to reset the status
    Status& Status::clear() {
        // Check if m_state is not null before deleting
        if (m_state != nullptr) {
            delete[] m_state;
            m_state = nullptr;
        }
        m_code = 0;
        return *this;
    }

    // Overloaded stream insertion operator
    std::ostream& operator<<(std::ostream& os, const Status& status) {
        if (!status) {
            if (status.m_code != 0) {
                os << "ERR#" << status.m_code << ": ";
            }
            os << status.m_state;
        }
        return os;
    }

};
