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
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H

#include <iostream>
#include <fstream> 

namespace sdds {

    // Abstract class representing the interface for a product
    class iProduct {
    public:
        // Virtual destructor for proper polymorphic behavior
        virtual ~iProduct() {}

        // Pure virtual function to display product information
        virtual std::ostream& display(std::ostream& ostr) const = 0;

        // Pure virtual function to read product information from input stream
        virtual std::istream& read(std::istream& istr) = 0;

        // Pure virtual function to set linear display mode
        virtual void linear(bool isLinear) = 0;

        // Pure virtual function to load product information from a file
        virtual std::ifstream& load(std::ifstream& ifstr) = 0;

        // Conversion operator to bool (checks if the product is valid)
        virtual operator bool() const = 0;

        // Conversion operator to double (returns the price of the product)
        virtual operator double() const = 0;

        // Pure virtual function to add quantity to the product
        virtual int operator+=(int qty) = 0;

        // Pure virtual function to subtract quantity from the product
        virtual int operator-=(int qty) = 0;

        // Pure virtual function to check if the product has a matching SKU
        virtual bool operator==(int sku) const = 0;

        // Pure virtual function to check if the product has a matching description
        virtual bool operator==(const char* description) const = 0;

        // Pure virtual function to get the quantity needed for the product
        virtual int qtyNeeded() const = 0;

        // Pure virtual function to get the current quantity on hand for the product
        virtual int qty() const = 0;

        // Pure virtual function to read SKU from input stream
        virtual int readSku(std::istream& istr) = 0;

        // Pure virtual function to save product information to a file
        virtual std::ofstream& save(std::ofstream& ofstr) const = 0;


        //pure virtual function which changes sku
        virtual int sku(int sku) = 0;

        // pure virtual to get sku
        virtual int getsku()  const = 0;
    };

    // Overloaded operator to output product information to an output stream
    std::ostream& operator<<(std::ostream& os, const iProduct& product);

    // Overloaded operator to read product information from an input stream
    std::istream& operator>>(std::istream& is, iProduct& product);
}

#endif 
