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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include  <fstream>
#include "Status.h"

namespace sdds {
    class Item : public iProduct {
        // Private member variables
        double m_price;
        int m_quantityOnHand;
        int m_qtyNeeded;
        char* m_description;
        bool m_isLinear;

    protected:
        // Protected member variables
        Status m_state;
        int m_sku;
        bool linear() const;

    public:
        // Constructors and destructor
        Item();
        virtual ~Item();
        Item(const Item& other);

        virtual Item& operator=(const Item& other);

        // Function to clear and reset the item
        void clear();

        // Overridden functions from the iProduct interface
        virtual void linear(bool isLinear) override;
        virtual int qtyNeeded() const override;
        virtual int qty() const override;
        virtual int sku(int sku)  override;
        virtual int getsku()  const override;
        virtual operator double() const override;
        virtual operator bool() const override;
        virtual int operator-=(int qty) override;
        virtual int operator+=(int qty) override;
        virtual bool operator==(int sku) const override;
        virtual bool operator==(const char* description) const override;
        virtual std::ofstream& save(std::ofstream& ofstr) const override;
        virtual std::ifstream& load(std::ifstream& ifstr) override;
        virtual std::ostream& display(std::ostream& ostr) const override;
        virtual int readSku(std::istream& istr) override;
        virtual std::istream& read(std::istream& istr) override;
    };


}

#endif // SDDS_ITEM_H
