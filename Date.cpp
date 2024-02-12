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
#include "Date.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace sdds {

    // Default constructor
    Date::Date() {
        ut.testMode(true);
        ut.getSystemDate(&m_year, &m_month , &m_day);

    }

    // Parameterized constructor
    Date::Date(int year, int month, int day) {
        m_year = year;
        m_month = month;
        m_day = day;
        check(); // Check the validity of the date
    }

    // Function to check the validity of the date
    bool Date::check() {
        int currentYear, currentMonth, currentDay;
        ut.testMode(true);
        ut.getSystemDate(&currentYear, &currentMonth, &currentDay);

        // Check if the year is within a valid range
        if (m_year < currentYear || m_year > MAX_YEAR) {
            status = "Invalid year in date";
            status = 1;
            return false;
        }

        // Check if the month is within a valid range
        if (m_month < 1 || m_month > 12) {
            status = "Invalid month in date";
            status = 2;
            return false;
        }

        // Check if the day is within a valid range
        int maxDaysInMonth = ut.daysOfMon(m_month, m_year);
        if (m_day < 1 || m_day > maxDaysInMonth) {
            status = "Invalid day in date";
            status = 3;
            return false;
        }

        status.clear(); // Clear the status if the date is valid
        return true;
    }

    // Get the status of the date
    const Status& Date::state() const {
        return status;
    }

    // Formatted function to set the formatted flag
    Date& Date::formatted(bool value) {
        m_formatted = value;
        return *this; // Return a reference to the current object.
    }

    // Conversion operator to check if the Date is in a valid state
    Date::operator bool() const {
        return (status);
    }

    // Calculate the unique integer value for the date
    int Date::uniqueDateValue(int year, int month, int day) const {
        return ((year * 372) + (month * 31) + day);
    }

    // Overloaded equality operator
    bool Date::operator==(const Date& other) const {
        return uniqueDateValue(m_year, m_month, m_day) == uniqueDateValue(other.m_year, other.m_month, other.m_day);
    }

    // Overloaded inequality operator
    bool Date::operator!=(const Date& other) const {
        return !(*this == other);
    }

    // Overloaded less than operator
    bool Date::operator<(const Date& other) const {
        return uniqueDateValue(m_year, m_month, m_day) < uniqueDateValue(other.m_year, other.m_month, other.m_day);
    }

    // Overloaded greater than operator
    bool Date::operator>(const Date& other) const {
        return uniqueDateValue(m_year, m_month, m_day) > uniqueDateValue(other.m_year, other.m_month, other.m_day);
    }

    // Overloaded less than or equal to operator
    bool Date::operator<=(const Date& other) const {
        return uniqueDateValue(m_year, m_month, m_day) <= uniqueDateValue(other.m_year, other.m_month, other.m_day);
    }

    // Overloaded greater than or equal to operator
    bool Date::operator>=(const Date& other) const {
        return uniqueDateValue(m_year, m_month, m_day) >= uniqueDateValue(other.m_year, other.m_month, other.m_day);
    }

    // Read function to input a Date from istream
    istream& Date::read(std::istream& istr) {
        int dateValue;

        if (!(istr >> dateValue)) {
            istr.setstate(std::ios::failbit);
            cerr << "Invalid date value";
            return istr;
        }

        int numDigits = 0;
        int temp = dateValue;

        // Count the number of digits in the dateValue
        while (temp > 0) {
            temp /= 10;
            numDigits++;
        }

        int currentYear, currentMonth, currentDay;
        ut.getSystemDate(&currentYear, &currentMonth, &currentDay);

        if (numDigits == 6) {
            // Process date in YYMMDD format
            m_year = (dateValue / 10000) + 2000;
            dateValue %= 10000;
            m_month = dateValue / 100;
            m_day = dateValue % 100;
            if (!check()) {
                istr.setstate(std::ios::failbit); // Invalid date format
                return istr;
            }
        }
        else if (numDigits == 4) {
            // Process date in MMDD format
            m_year = currentYear;
            m_month = dateValue / 100;
            m_day = dateValue % 100;
            if (!check()) {
                istr.setstate(std::ios::failbit); // Invalid date format
                return istr;
            }
        }
        else {
            // Process date in YYMMDD format
            m_year = currentYear;
            m_month = dateValue / 100;
            m_day = dateValue % 100;
            if (!check()) {
                istr.setstate(std::ios::failbit); // Invalid date format
                return istr;
            }
        }

        return istr;
    }

    // Write function to output a Date to ostream
    ostream& Date::write(std::ostream& ostr) const {
        if (m_formatted) {
            // Output date in YYYY/MM/DD format
            ostr << setw(4) << setfill('0') << m_year << '/'
                << setw(2) << setfill('0') << m_month << '/'
                << setw(2) << setfill('0') << m_day;
        }
        else {
            // Output date in YYMMDD format
            ostr << setfill('0') << setw(2) << (m_year % 100)
                << setw(2) << setfill('0') << m_month
                << setw(2) << setfill('0') << m_day;
        }
        return ostr;
    }


    // Overload the insertion operator to write a Date object to an ostream.
    ostream& operator<<(ostream& os, const Date& date) {
        date.write(os);
        return os;
    }

    // Overload the extraction operator to read a Date object from an istream.
    istream& operator>>(istream& is, Date& date) {
        date.read(is);
        return is;
    }

}  
