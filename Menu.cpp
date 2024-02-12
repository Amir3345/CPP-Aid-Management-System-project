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
#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include "Menu.h"

using namespace std;

namespace sdds {
    Menu::Menu() : menuContent(nullptr), numOptions(0) {
        
    }
    // Constructor
    Menu::Menu(const char* content)
        : menuContent(nullptr), numOptions(0)
    {
        int numTabs = 0;
        if (content == nullptr || strlen(content) == 0) {
            cerr << "Invalid Menu!" << endl;
        }
        else {
            for (size_t i = 0; i < strlen(content); i++) {
                if (content[i] == '\t') {
                    numTabs++;
                }
            }

            numOptions = numTabs + 1;
            if (numOptions > maxoptions) {
                cerr << "Invalid Menu!" << endl;
            }
            else {
                menuContent = new char[strlen(content) + 1];
                strcpy(menuContent, content);
            }
        }
    }

    // Run the menu and get user's choice
    unsigned int Menu::run() const {
        int i, counter = 1, flag = 0;
        unsigned int choice = 0;

        if (menuContent) {
            // Display menu options
            cout << counter << "- ";
            for (i = 0; menuContent[i] != '\0'; i++) {
                if (menuContent[i] == '\t') {
                    counter++;
                    cout << endl;
                    cout << counter << "- ";
                }
                else {
                    cout << menuContent[i];
                }
            }
            cout << endl;
            cout << "---------------------------------" << endl;
            cout << "0- Exit" << endl;

            // Get user input
            while (!flag) {
                cout << "> ";
                if (cin >> choice) {
                    if (choice >= 0 && choice <= numOptions) {
                        flag = true;
                    }
                    else {
                        cout << "Value out of range [0<=val<=" << numOptions << "]: ";
                        cin >> choice;
                        flag = true;
                    }
                }
                else {
                    cout << "Invalid Integer, retry: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> choice;
                    flag = true;
                }
            }
        }
        return choice;
    }


    // Destructor
    Menu::~Menu() {
        delete[] menuContent;
    }

}  
