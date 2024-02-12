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

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <ostream>

namespace sdds {


    class Status {
        char* m_state;
        int m_code;

    public:
        Status();
        Status(const Status& s);
        Status(const char* desc, int code);
        ~Status();
        Status& operator=(const Status& s);
        Status& operator=(int sCode);
        Status& operator=(const char* state);
        operator int() const;
        operator const char* () const;
        operator bool() const;

        Status& clear();
        friend std::ostream& operator<<(std::ostream& os, const Status& status);
    };

}

#endif 