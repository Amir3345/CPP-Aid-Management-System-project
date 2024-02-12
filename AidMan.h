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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"


namespace sdds {
    const int sdds_max_num_items = 100; 
    class AidMan {
        char* filename;
        int m_noOfItems;
        iProduct* iProductPointers[sdds_max_num_items];
        Menu mainMenu;

       
      
         int menu() const;
        AidMan(const AidMan& other) = delete;  
        AidMan& operator=(const AidMan& other) = delete;  


        void save();
        void allocate(const char* Dname);
        void deallocate();
        bool load();
        int list(const char* sub_desc = nullptr);
        
        int search(int sku) const;
        void addItem();
      
        void remove(int index);
        void removeItem();
        
        void updateQuantity();

        void sort();
        
        void shipItems();
        
    public:
        AidMan();
        AidMan(const char* filename);
        ~AidMan();
        void run();
      
    };
}
#endif 
