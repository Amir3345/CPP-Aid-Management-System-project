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
#include <iomanip>
#include <iostream>
#include <cstring>
#include "Item.h"


using namespace std;

namespace sdds {

    // Constructor
    Item::Item() : m_price(0.0), m_quantityOnHand(0), m_qtyNeeded(0), m_description(nullptr), m_isLinear(false),
        m_state(Status()), m_sku(0) {
      
    }

    // Copy constructor
    Item::Item(const Item& other) {
        // Perform deep copy
        m_sku = other.m_sku;
        m_price = other.m_price;
        m_quantityOnHand = other.m_quantityOnHand;
        m_qtyNeeded = other.m_qtyNeeded;
        m_isLinear = other.m_isLinear;

        // Deep copy for dynamically allocated resources (description)
        if (other.m_description) {
            m_description = new char[strlen(other.m_description) + 1];
            strcpy(m_description, other.m_description);
        }
        else {
            m_description = nullptr;  // Handle the case where other.m_description is null
        }

        m_state = other.m_state;
    }



    Item& Item::operator=(const Item& other) {
        if (this != &other) { // Avoid self-assignment
            // Copy other members
            m_sku = other.m_sku;
            m_price = other.m_price;
            m_quantityOnHand = other.m_quantityOnHand;
            m_qtyNeeded = other.m_qtyNeeded;

            // Deallocate existing memory for description
            delete[] m_description;
            m_description = nullptr;

            // Allocate memory for description and copy content
            if (other.m_description != nullptr) {
                m_description = new char[std::strlen(other.m_description) + 1];
                std::strcpy(m_description, other.m_description);
            }
        }
        return *this;
    }



    // Destructor
    Item::~Item() {
        // Cleanup dynamically allocated resources
        clear();
    }

    // Clear function to release resources
    void Item::clear() {
        delete[] m_description;
        m_description = nullptr;

        // Reset other member variables
        m_price = 0.0;
        m_quantityOnHand = 0;
        m_qtyNeeded = 0;
        m_isLinear = false;
        m_state.clear();
        m_sku = 0;
    }

    // Query to return linear flag
    bool Item::linear() const {
        // Linear logic
        return m_isLinear;
    }

    //to get SKU function
    int Item::getsku() const {
        return m_sku;
    }

    int Item::sku(int sku) 
    { return m_sku = sku; }

    // Implementation of iProduct interface functions
    int Item::qtyNeeded() const {
        return m_qtyNeeded;
    }

    int Item::qty() const {
        return m_quantityOnHand;
    }

    // Conversion operator for double
    Item::operator double() const {
        return m_price;
    }

    // Conversion operator for bool
    Item::operator bool() const {

    
            return m_sku != 0;
        //return m_state.operator bool();
    }

    // Operator to decrease quantity on hand
    int Item::operator-=(int qty) {
        m_quantityOnHand -= qty;
        return m_quantityOnHand;
    }

    // Operator to increase quantity on hand
    int Item::operator+=(int qty) {
        m_quantityOnHand += qty;
        return m_quantityOnHand;
    }

    // Set the linear flag
    void Item::linear(bool isLinear) {
        m_isLinear = isLinear;
    }

    // Operator to check equality with SKU
    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    // Operator to check equality with a substring of the description
    bool Item::operator==(const char* substring) const {
        return m_description && substring && strstr(m_description, substring) != nullptr;
    }

    // Save function to write the object to a file
    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (m_state) {
            ofstr << m_sku << '\t' << m_description << '\t' << m_quantityOnHand << '\t'
                << m_qtyNeeded << '\t' << std::fixed << std::setprecision(2) << m_price;
        }
        return ofstr;
    }

    // Load function to read the object from a file
    std::ifstream& Item::load(std::ifstream& ifstr) {
        // Clear existing data before loading
        clear();

        // Allocate memory for dynamic attributes
        m_description = nullptr;

        // Read data from the file
        ifstr >> m_sku;

        // Check if the read was successful
        if (ifstr.fail()) {
            m_state = "Input file stream read failed!";
            return ifstr;
        }

        // Read the rest of the attributes
        ifstr.ignore(); // Discard the tab character

        // Dynamically allocate memory for description
        char temp[4096]; // Adjust the size as per your needs
        ifstr.getline(temp, 4096, '\t');
        m_description = new char[strlen(temp) + 1];
        strcpy(m_description, temp);

        // Read other attributes
        ifstr >> m_quantityOnHand >> m_qtyNeeded >> m_price;

        // Check if the read was successful
        if (ifstr.fail()) {
            m_state = "Input file stream read failed!";
        }

        // Discard the newline character
        ifstr.ignore();

        return ifstr;
    }

    // Display function to output the object's information
    std::ostream& Item::display(std::ostream& ostr) const {
        if (m_state) {
            if (linear()) {
                // Truncate the description if it exceeds 35 characters
                ostr << setw(5) << m_sku << " | " << setw(35) << left
                    << (strlen(m_description) > 35 ? string(m_description, 0, 35) : m_description) << " | "
                    << setw(4) << right << m_quantityOnHand << " | " << setw(4) << right << m_qtyNeeded << " | "
                    << setw(7) << right << fixed <<setprecision(2) << m_price << " |";
            }
            else {
                // Display non-linear information
                ostr << "AMA Item:" << endl;
                ostr << setw(5) << m_sku << ": " << m_description << endl;
                ostr << "Quantity Needed: " << m_qtyNeeded << endl;
                ostr << "Quantity Available: " << m_quantityOnHand << endl;
                ostr << "Unit Price: $" << fixed << setprecision(2) << m_price << endl;
                ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << (m_qtyNeeded - m_quantityOnHand) * m_price << endl;
            }
        }
        else {
            // Display error message
            ostr << m_state;
        }
        return ostr;
    }

    // Read SKU function to input the SKU from the console
    int Item::readSku(istream& istr) {
        int value;

        cout << "SKU: ";

        while (true) {
            istr >> value;

            if (istr.fail()) {
                istr.clear();
                istr.ignore(2000, '\n'); istr.clear();
                istr.ignore(2000, '\n');
                cout << "Invalid Integer, retry: ";
            }
            else if (value < 40000 || value > 99999) {
                cout << "Value out of range [40000<=val<=99999]: ";
            }
            else {
                this->m_sku = value;
                return value;
            }
        }
    }

    // Read function to input the object from the console
    istream& Item::read(istream& istr) {
        // Clear existing data
        delete[] m_description;
        m_state.clear();

        // Display title
        cout << "AMA Item:" << endl;

        cout << "SKU: " << m_sku << endl;

        // Read Description
        cout << "Description: ";
        char temp[2000];
        istr.ignore();
        istr.getline(temp, 2000);
        m_description = new char[strlen(temp) + 1];
        strcpy(m_description, temp);

        // Read Quantity Needed
        cout << "Quantity Needed: ";
        while (true) {
            int temp;
            istr >> temp;

            if (istr.fail()) {
                istr.clear();
                istr.ignore(2000, '\n');
                cout << "Invalid Integer, retry: ";
            }
            else if (temp < 1 || temp > 9999) {
                cout << "Value out of range [1<=val<=9999]: ";
            }
            else {
                this->m_qtyNeeded = temp;
                break;
            }
        }

        // Read Quantity On Hand
        cout << "Quantity On Hand: ";
        while (true) {
            int temp;
            istr >> temp;

            if (istr.fail()) {
                istr.clear();
                istr.ignore(2000, '\n');
                cout << "Invalid Integer, retry: ";
            }
            else if (temp < 0 || temp > m_qtyNeeded) {
                cout << "Value out of range [0<=val<=" << m_qtyNeeded << "]: ";
            }
            else {
                this->m_quantityOnHand = temp;
                break;
            }
        }

        // Read Unit Price
        cout << "Unit Price: $";
        while (true) {
            double temp;
            istr >> temp;

            if (istr.fail()) {
                istr.clear();
                istr.ignore(2000, '\n');
                cout << "Invalid number, retry: ";
            }
            else if (temp < 0 || temp > 9999.00) {
                cout << "Value out of range [0.00<=val<=9999.00]: ";
            }
            else {
                this->m_price = temp;
                break;
            }
        }

        // Validate input
        if (!istr) {
            cout << "Console entry failed!" << endl;
            m_state = "Console entry failed!";
        }

        return istr;
    }
}
