#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <limits>
#include "Perishable.h"


using namespace std;
namespace sdds {

    Perishable::Perishable() : Item(), m_expiry(""), m_handling(nullptr) {}

    Perishable::~Perishable() {
        delete[] m_handling;
    }

    Perishable::Perishable(const Perishable& other) :Item(other), m_expiry(other.m_expiry), m_handling(nullptr) {
        if (other.m_handling) {
            m_handling = new char[std::strlen(other.m_handling) + 1];
            std::strcpy(m_handling, other.m_handling);
        }
    }


    const string& Perishable::expiry() {
        static string formattedExpiry;

        formattedExpiry = "20" + m_expiry.substr(0, 2) + "/" + m_expiry.substr(2, 2) + "/" + m_expiry.substr(4, 2);
        return formattedExpiry;
    }


    Perishable& Perishable::operator=(const Perishable& other) {
        if (this != &other) { // Avoid self-assignment
            // Use the base class copy assignment operator
            Item::operator=(other);

            // Copy Perishable class members
            m_expiry = other.m_expiry;

            // Allocate memory for handling instructions and copy content
            delete[] m_handling;
            m_handling = nullptr;
            if (other.m_handling != nullptr) {
                m_handling = new char[std::strlen(other.m_handling) + 1];
                std::strcpy(m_handling, other.m_handling);
            }
        }
        return *this;
    }




    int Perishable::readSku(std::istream& is) {
        int value = 0;

        cout << "SKU: ";

        while (true) {
            is >> value;

            if (is.fail()) {
                is.clear();
                is.ignore(2000, '\n');
                cout << "Invalid Integer, retry: ";
            }
            else if (value < 10000 || value > 39999 || value / 10000 < 1 || value / 10000 > 3) {
                cout << "Value out of range [10000<=val<=39999]: ";
            }

            else {
                this->m_sku = value;
                return value;
            }
        }
    }


    std::ifstream& Perishable::load(std::ifstream& file) {
        string tempHandling;

        Item::load(file);

        delete[] m_handling;
        m_handling = nullptr;

        // Read handling instructions from file
        getline(file, tempHandling, '\t');

        // Read expiry from file
        file >> m_expiry;

        // Ignore newline
        file.ignore();

        if (file.fail()) {
            m_state = "Input file stream read (perishable) failed!";
        }
        else {
            if (!tempHandling.empty() && tempHandling != " ") {
                m_handling = new char[tempHandling.length() + 1];
                strcpy(m_handling, tempHandling.c_str());
            }
        }

        return file;
    }

    std::ostream& Perishable::display(std::ostream& os) const {
        if (Item::m_state) {


            if (Item::linear()) {
                os.clear();
                Item::display(os);
                os << (m_handling != nullptr && m_handling[0] != '\0' ? "*" : " ");
                os << "20" << m_expiry[0] << m_expiry[1] << "/" << m_expiry[2] << m_expiry[3] << "/" << m_expiry[4] << m_expiry[5];

            }
            else {
                os << "Perishable ";
                Item::display(os);
                os << "Expiry date: " << "20" << m_expiry[0] << m_expiry[1] << "/" << m_expiry[2] << m_expiry[3] << "/" << m_expiry[4] << m_expiry[5] << endl;
                if (m_handling != nullptr && m_handling[0] != '\0') {

                    os << "Handling Instructions: " << m_handling << endl;
                }
            }
        }
        else
        {
            //displays state as error message
            os << m_state;

        }
        return os;
    }

    std::ofstream& Perishable::save(std::ofstream& file) const {

        Item::save(file);
        file << '\t';

        if (m_handling && strlen(m_handling) > 0) {
            file << m_handling << '\t';
        }
        else {
            file << "\t";
        }

        file << m_expiry;

        return file;
    }

    std::istream& Perishable::read(std::istream& is) {


        Item::read(is);
        delete[] m_handling;
        m_handling = nullptr;

        std::cout << "Expiry date (YYMMDD): ";
        is >> m_expiry;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        std::cout << "Handling Instructions, ENTER to skip: ";
        if (is.peek() != '\n') {
            // Read handling instructions into a string
            std::string handlingInstructions;
            std::getline(is, handlingInstructions);

            // Dynamically allocate memory for m_handling
            delete[] m_handling;
            m_handling = new char[handlingInstructions.length() + 1];

            // Copy the string content to m_handling
            std::strcpy(m_handling, handlingInstructions.c_str());
        }
        else {
            is.ignore(); // consume the newline character
        }


        // Validate input
        if (!is) {
            cout << "Console entry failed!" << endl;
            m_state = "Console entry failed!";
        }

        return is;
    }
}
