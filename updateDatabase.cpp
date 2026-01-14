#include "UpdateDatabaseHeader.h"
#include <iostream>
#include <sqlite3.h>
#include "Statement.h"
#include <string>
#include <istream>
#include <stdexcept>

bool executeStatement(Statement& stmt) {
    int rc = sqlite3_step(stmt.get());
    if (rc == SQLITE_DONE) return true;

    return false;
}

void createEntry(sqlite3* db) {
    Statement stmt(db, "INSERT INTO BOOKS (title, author, available) VALUES (?, ?, ?)");

    std::string title;
    std::string author;
    bool available = true;

    std::cout << "\n";
    std::cout << "Please enter the title of the book: ";
    std::getline(std::cin >> std::ws, title);
    std::cout << "\n";
    std::cout << "Please enter the author's name: ";
    std::getline(std::cin >> std::ws, author);
    std::cout << "\n";

    if (sqlite3_bind_text(stmt.get(), 1, title.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
        throw std::runtime_error("Failed to bind author");

    if (sqlite3_bind_text(stmt.get(), 2, author.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
        throw std::runtime_error("Failed to bind title");

    if (sqlite3_bind_int(stmt.get(), 3, available ? 1 : 0) != SQLITE_OK)
        throw std::runtime_error("Failed to bind availability");

    if (executeStatement(stmt)) {
        std::cout << title << " added successfully!\n";
        std::cout << "\n";
    }
    else {
        throw std::runtime_error("Failed to add new entry");
    }
}

void editEntry() {

};

void removeEntry() {


};
