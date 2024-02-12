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
#include <fstream>
#include <iomanip>
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "Item.h"
#include "Perishable.h"
#include "Utils.h"

using namespace std;

namespace sdds {
    AidMan::AidMan() : filename(nullptr), m_noOfItems(0), mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
    }

        // Constructor
        AidMan::AidMan(const char* file) {
            const char* m_default = "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database";
            new (&mainMenu) Menu(m_default);
            if (file != nullptr) {
                filename = new char[strlen(file) + 1];
                strcpy(filename, file);
            }
            else {
                filename = nullptr;
            }
        }

        // Destructor
        AidMan::~AidMan() {
            delete[] filename;
            for (int i = 0; i < m_noOfItems; i++) {
                delete iProductPointers[i];
            }
        }

        //part 1
        
        // Display menu and return user's choice
        int AidMan::menu() const {
            cout << "Aid Management System\n";
            Date date;
            cout << "Date: " << date << "\n";
            if (filename != nullptr) {
                cout << "Data file: " << filename << "\n";
            }
            else {
                cout << "Data file: No file\n";
            }
            cout << "---------------------------------" << endl;

            return mainMenu.run();
        }

        // Run the Aid Management System
        void AidMan::run() {
            int option = -1;


            while (option != 0)
            {

                option = menu();


                // Process user's choice
                if (filename == nullptr && option != 7 && option != 0) {

                    option = 7;
                }

                switch (option) {
                case 1:
                    cout << "\n****List Items****\n";
                    list();
                    break;
                case 2:
                    cout << "\n****Add Item****\n";
                    addItem();
                    cout << endl;
                    break;
                case 3:
                    cout << "\n****Remove Item****\n";
                    removeItem();
                    break;
                case 4:
                    cout << "\n****Update Quantity****\n";
                    updateQuantity();
                    break;
                case 5:
                    cout << "\n****Sort****\n";
                    sort();
                    cout << endl;
                    
                    break;
                case 6:
                    cout << "\n****Ship Items****\n";
                    shipItems();
                    cout << endl;
                    break;
                case 7:
                    cout << "\n****New/Open Aid Database****\n";
                    if (load() == true) {
                        cout << m_noOfItems << " records loaded!" << endl << endl;
                    }
                    break;
                case 0:
                    cout << "Exiting Program!\n";
                    save();
                    break;
                default:
                    break;
                }

            }

        }
        // Save data records in file
        void AidMan::save() {
            if (filename != nullptr) {
                std::ofstream ofstr;
                ofstr.open(filename);
                for (int i = 0; i < m_noOfItems; i++) {
                    iProductPointers[i]->save(ofstr);
                    ofstr << endl;
                }
            }
        }

        // Deallocate all the memory allocated by the class
        void AidMan::allocate(const char* Dname) {
            delete[] filename;

            if (Dname != nullptr) {
                filename = new char[strlen(Dname) + 1];
                for (int i = 0; i < (int)strlen(Dname) + 1; i++)
                    filename[i] = Dname[i];
            }
            else {
                filename = nullptr;
            }
        }

        void AidMan::deallocate() {
            for (int i = 0; i < m_noOfItems; i++) {
                delete iProductPointers[i];
            }
            m_noOfItems = 0;
        }

        // Load data records from a data file
        bool AidMan::load() {
            int choice;
            char fname[100];
            char Digit;
            int i = 0;
            m_noOfItems = 0;
            save();
            deallocate();


            cout << "Enter file name: ";
            cin >> fname;
            allocate(fname);


            if (filename != nullptr) {

                ifstream file;
                file.open(filename);

                if (!file.is_open()) {
                    cout << "Failed to open " << filename << " for reading!" << endl;
                    cout << "Would you like to create a new data file?" << endl;
                    cout << "1- Yes!" << endl;
                    cout << "0- Exit" << endl;
                    cout << "> ";


                    cin >> choice;

                    if (choice == 1) {
                        // Create an empty file
                        ofstream out(filename);

                    }
                    else if (choice == 0) {
                        delete[] filename;
                        filename = nullptr;
                    }
                    else {
                        cout << "input a vaild selection 1 or 0" << endl;
                    }
                }
                else {
                    while (!file.eof()) {
                        Digit = file.peek();
                        if (Digit == '1' || Digit == '2' || Digit == '3') {
                            iProductPointers[m_noOfItems] = new Perishable;
                        }
                        else if (Digit == '4' || Digit == '5' || Digit == '6' || Digit == '7' || Digit == '8' || Digit == '9') {
                            iProductPointers[m_noOfItems] = new Item;
                        }
                        else {
                            file.setstate(ios::failbit);
                        }
                        if (file.good()) {
                            iProductPointers[m_noOfItems]->load(file);
                            if (file.good()) {
                                m_noOfItems++;
                            }
                            else {
                                delete iProductPointers[i];
                            }
                        }
                    }
                }
        
                return m_noOfItems > 0 ? true : false;
            }
            cout << "file name is empty" << endl;
            return 0;
        }

        //part 1
        // List items
        int AidMan::list(const char* sub_desc) {

            int i = 0, num = 0;
            char option;

            if (sub_desc == nullptr) {
                if (m_noOfItems != 0) {
                    cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
                    cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

                    for (i = 0; i < m_noOfItems; i++) {
                        cout.width(4);
                        cout.fill(' ');
                        cout << i + 1 << " | ";
                        iProductPointers[i]->linear(true);
                        iProductPointers[i]->display(cout);
                        cout << endl;
                    }

                    cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
                    cout << "Enter row number to display details or <ENTER> to continue:" << endl;
                    cout << "> ";

                    cin.ignore(2000, '\n');
                    option = cin.get();

                    if (option != '\n') {
                        num = static_cast<int>(option - '0');
                        iProductPointers[num - 1]->linear(false);
                        iProductPointers[num - 1]->display(cout);
                        cout << endl;
                    }

                    cout << endl;
                }
                else {
                    cout << "The list is empty!" << endl;
                }
            }
            else {
                cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
                cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

                for (i = 0; i < m_noOfItems; i++) {
                    if (*iProductPointers[i] == sub_desc) {
                        cout.width(4);
                        cout << i + 1 << " | ";
                        iProductPointers[i]->linear(true);
                        iProductPointers[i]->display(cout);
                        cout << endl;
                        num++;
                    }
                }

                cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            }

            return num;
        }



        //part 2


        int AidMan::search(int sku) const {
            // Check if the SKU is 0, indicating an abort
            if (sku == 0) {
                cout << "Aborted!" << endl;
                return -1;
            }

            // Loop through the array of iProductPointers to find a matching SKU
            for (int i = 0; i < m_noOfItems; i++) {
                if (iProductPointers[i] != nullptr) {
                    // Compare SKU with the SKU of the current iProduct
                    if (iProductPointers[i]->getsku() == sku) {
                        cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
                        return i; // Return the index if a match is found
                    }
                }
            }
            return -1; // Return -1 if no match is found
        }

        void AidMan::addItem() {
            // Check if the maximum number of items has been reached
            if (m_noOfItems >= sdds_max_num_items) {
                cout << "Database full!" << endl;
                return;
            }

            int userInput;
            cout << "1- Perishable\n"
                << "2- Non-Perishable\n"
                << "-----------------\n"
                << "0- Exit\n> ";
            cin >> userInput;

            // Check if the user input is 0, indicating an abort
            if (userInput == 0) {
                cout << "Aborted!" << endl;
                return;
            }

            int inputSku;

            // Validate and read SKU input within the specified range
            while (true) {
                cout << "SKU: ";
                cin >> inputSku;

                // Check if the entered SKU is within the valid range
                if (inputSku >= 10000 && inputSku <= 99999) {
                    break;  // Exit the loop if a valid SKU is entered
                }
                else {
                    cin.clear();  // Clear the error flag
                    cin.ignore(2000, '\n');  // Discard invalid input
                    cout << "Invalid input. Please enter a value in the range [10000<=val<=99999]." << endl;
                }
            }

            // Search for the SKU in the current iProductPointers array before allocating/freeing up space in iProductPointers 
            int result = search(inputSku);

            // Check if the SKU already exists in the system
            if (result == -1) {
                // SKU does not exist, proceed with adding a new item based on user input
                if (userInput == 1) {
                    // Check if the number of items is less than the maximum before creating a new Perishable item
                    if (m_noOfItems < sdds_max_num_items) {
                        iProductPointers[m_noOfItems] = new Perishable();
                        iProductPointers[m_noOfItems]->sku(inputSku);
                        iProductPointers[m_noOfItems]->read(cin);
                        m_noOfItems++;
                    }
                }
                else if (userInput == 2) {
                    // Check if the number of items is less than the maximum before creating a new Non-Perishable item
                    if (m_noOfItems < sdds_max_num_items) {
                        iProductPointers[m_noOfItems] = new Item();
                        iProductPointers[m_noOfItems]->sku(inputSku);
                        iProductPointers[m_noOfItems]->read(cin);
                        m_noOfItems++;
                    }
                }
            }
        }





















        //part 3

        void AidMan::remove(int index) {
            int choice;

            if (index < 0 || index >= m_noOfItems) {
                cout << "Invalid index!" << endl;
                return;
            }

            // Print the item details before removal
            cout << "Following item will be removed: "<< endl;
            iProductPointers[index]->linear(false);
            iProductPointers[index]->display(cout) << endl;
            cout << "Are you sure?" << endl;
            cout << "1- Yes!" << endl;
            cout << "0- Exit" << endl;
            cout << "> ";

          
            cin >> choice;

            if (choice == 1) {
                delete iProductPointers[index];
                // Shift the remaining items to the left
                for (int i = index; i < m_noOfItems - 1; i++) {
                    iProductPointers[i] = iProductPointers[i + 1];
                }
                m_noOfItems--;

                cout << "Item removed!" << endl;
            }
            else {
                cout << "Aborted!" << endl;
            }
        }

        void AidMan::removeItem() {
            int sku;
            char Cstring[100];
            int count = 0;
            int foundIndexes[sdds_max_num_items];
            int i, y;

            cout << "Item description: ";
       
            cin.ignore();
            cin.getline(Cstring, 100);

          

            // Find items with the specified description
            for (i = 0; i < m_noOfItems; i++) {
                if (iProductPointers[i]->operator==(Cstring)) {
                    foundIndexes[count++] = i;
                }
            }

            // If no items found, print a message
            if (count == 0) {
                cout << "No items found with the specified description." << endl;
                return;
            }

            // List the found items
            cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            for ( y = 0; y < count; y++) {
                cout.width(4);
                cout.fill(' ');
                cout << foundIndexes[y] + 1  << " | ";
                iProductPointers[foundIndexes[y]]->linear(true);
                iProductPointers[foundIndexes[y]]->display(cout);
                cout << endl;
               
            }
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

            // Ask for SKU to remove
          
            while (true) {
                cout << "Enter SKU: ";

                if (cin >> sku && sku >= 10000 && sku <= 99999) {
                    break;  // Exit the loop if a valid SKU is entered
                }
                else {
                    cin.clear();  // Clear the error flag
                    cin.ignore(2000, '\n');  // Discard invalid input
                    cout << "Invalid input. Please enter a value in the range [10000, 99999]." << endl;
                }
            }

            int foundIndex = -1;

            // Find the index of the item with the specified SKU
            for (int i = 0; i < count; i++) {
                if (iProductPointers[foundIndexes[i]]->operator==(sku) ) {
                    foundIndex = foundIndexes[i];
                    break;
                }
            }

            // If SKU not found, print a message
            if (foundIndex == -1) {
                cout << "SKU not found!" << endl;
                return;
            }

            // Remove the item
            remove(foundIndex);
            cout << endl;
        }




        //part 4
        void AidMan::updateQuantity() {
            int sku;
            char Cstring[100];
            int count = 0;
            int foundIndexes[sdds_max_num_items];
            int i, y;
            int choice;
            int quantity;

            cout << "Item description: ";

            cin.ignore();
            cin.getline(Cstring, 100);



            // Find items with the specified description
            for (i = 0; i < m_noOfItems; i++) {
                if (iProductPointers[i]->operator==(Cstring)) {
                    foundIndexes[count++] = i;
                }
            }

            // If no items found, print a message
            if (count == 0) {
                cout << "No items found with the specified description." << endl;
                return;
            }

            // List the found items
            cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            for (y = 0; y < count; y++) {
                cout.width(4);
                cout.fill(' ');
                cout << foundIndexes[y] + 1 << " | ";
                iProductPointers[foundIndexes[y]]->linear(true);
                iProductPointers[foundIndexes[y]]->display(cout);
                cout << endl;

            }
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

            // Ask for SKU to remove

            while (true) {
                cout << "Enter SKU: ";

                if (cin >> sku && sku >= 10000 && sku <= 99999) {
                    break;  // Exit the loop if a valid SKU is entered
                }
                else {
                    cin.clear();  // Clear the error flag
                    cin.ignore(2000, '\n');  // Discard invalid input
                    cout << "Invalid input. Please enter a value in the range [10000, 99999]." << endl;
                }
            }

            int foundIndex = -1;

            // Find the index of the item with the specified SKU
            for (int i = 0; i < count; i++) {
                if (iProductPointers[foundIndexes[i]]->operator==(sku)) {
                    foundIndex = foundIndexes[i];
                    break;
                }
            }

            // If SKU not found, print a message
            if (foundIndex == -1) {
                cout << "SKU not found!" << endl;
                return;
            }
            else {
                // Display options for quantity update
                cout << "1- Add" << endl;
                cout << "2- Reduce" << endl;
                cout << "0- Exit" << endl;
                cout << "> ";
                cin >> choice;
                // Calculate the difference between needed quantity and current quantity
                int qtyDifference = iProductPointers[foundIndex]->qtyNeeded() - iProductPointers[foundIndex]->qty();

                switch (choice) {
                case 1:
                    if (qtyDifference == 0) {
                        cout << "Quantity Needed already fulfilled!" << endl;
                        break;
                    }
                    // Prompt user for quantity to add within the valid range
                    cout << "Quantity to add: ";
                    cin >> quantity;
                    while (quantity > qtyDifference) {
                        cout << "Value out of range [1<=val<=" << qtyDifference << "]: ";
                        cin >> quantity;
                    }
                    // Update quantity and display message
                    iProductPointers[foundIndex]->operator+=(quantity);
                    cout << quantity << " items added!" << endl;
                    break;
                case 2:
                    if (iProductPointers[foundIndex]->qty() == 0) {
                        cout << "Quantity on hand is zero!" << endl;
                        break;
                    }
                    // Prompt user for quantity to reduce within the valid range
                    cout << "Quantity to reduce: ";
                    cin >> quantity;
                    while (quantity > iProductPointers[foundIndex]->qty()) {
                        cout << "Value out of range [1<=val<=" << iProductPointers[foundIndex]->qty() << "]: ";
                        cin >> quantity;
                    }
                    // Update quantity and display message
                    iProductPointers[foundIndex]->operator-=(quantity);
                    cout << quantity << " items removed!" << endl;
                    break;
                case 0:
                    cout << "Aborted!" << endl;
                    break;
                default:
                    break;
                }
                cout << endl;
            }
        }










        // part 5

        void AidMan::sort() {
            // Bubble sort based on the difference between needed quantity and current quantity
            for (int i = 0; i < m_noOfItems - 1; i++) {
                for (int j = i + 1; j < m_noOfItems; j++) {
                    // Calculate the differences for the current and next product
                    int diff1 = iProductPointers[i]->qtyNeeded() - iProductPointers[i]->qty();
                    int diff2 = iProductPointers[j]->qtyNeeded() - iProductPointers[j]->qty();

                    // Compare differences and swap if needed
                    if (diff2 > diff1) {
                        // Swap pointers
                        iProduct* temp = iProductPointers[i];
                        iProductPointers[i] = iProductPointers[j];
                        iProductPointers[j] = temp;
                    }
                }
            }

            // Display a message indicating the completion of the sort
            cout << "Sort completed!" << endl;
        }
            
        











        // part 6
        void AidMan::shipItems() {
            int shippedItems = 0;
            int year, month, day;
            ut.getSystemDate(&year, &month, &day);
            ofstream shippingFile("shippingOrder.txt");
            shippingFile << "Shipping Order, Date: " << year << "/" << month << "/" << "0" << day << endl;

            shippingFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
            shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            // Iterate through all iProduct Pointers elements
            for (int i = 0; i < m_noOfItems; i++) {
                // If the quantity needed and quantity on hand of the product is a match
                if (iProductPointers[i]->qtyNeeded() == iProductPointers[i]->qty()) {
                    shippedItems++;
                    // Print it in the linear format into the file
                    shippingFile.width(4);
                    shippingFile.fill(' ');
                    shippingFile << shippedItems << " | ";
                    iProductPointers[i]->linear(true);
                    iProductPointers[i]->display(shippingFile);
                    shippingFile << endl;

                    // Remove it from the iProduct Pointers array
                    delete iProductPointers[i];
                    iProductPointers[i] = nullptr;

                    
                }
            }

            // Print the end of the table in the file
            shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------"<<endl;

            // Print the number of items shipped on the screen
            cout << "Shipping Order for " << shippedItems << " times saved!" << endl;

            // Shift the valid pointers to the beginning of the array
            int validIndex = 0;
            for (int i = 0; i < m_noOfItems; i++) {
                if (iProductPointers[i] != nullptr) {
                    iProductPointers[validIndex++] = iProductPointers[i];
                }
            }

       
            // Update the number of items
            m_noOfItems = validIndex;
        }





}