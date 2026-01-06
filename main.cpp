// LibraryManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UpdateDatabaseHeader.h"
#include "SearchDatabaseHeader.h"
#include <mysqlx/xdevapi.h>
#include <iostream>

int main()
{
    bool running = true;
    while (running) {
        std::cout << "Welcome to the Library Database Management Tool!" << "\n" << std::endl;
        std::cout << "Please select from the following options: " << std::endl;
        std::cout << "1. Search database" << std::endl;
        std::cout << "2. Create new entry" << std::endl;
        std::cout << "3. Update an entry" << std::endl;
        std::cout << "4. Delete an entry" << std::endl;
        std::cout << "5. View current database" << std::endl;
        std::cout << "6. Quit" << "\n" << std::endl;

        std::cout << "Enter your choice: ";
        std::cout << std::endl;

        int choice;
        std::cin >> choice;
        switch (choice) {
        case 1:
            lookupEntry();
            break;
        case 2:
            createEntry();
            break;
        case 3:
            editEntry();
            break;
        case 4:
            removeEntry();
            break;
        case 5:
            viewAllEntries();
            break;
        case 6:
            running = false;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
        }
    }
    std::cout << std::endl;
    std::cout << "Thank you! Goodbye!";
    return 0;
}
