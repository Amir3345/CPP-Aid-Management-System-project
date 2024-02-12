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

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
    const int maxoptions = 15;
    class Menu {
    private:
        char* menuContent;
        unsigned int numOptions;
        
    public:
        Menu();
        Menu(const char* content);     
        ~Menu();                        
        
        Menu(const Menu& other) ;
        Menu& operator=(const Menu& other) = delete;
        unsigned int run() const;     
    };
}
#endif 