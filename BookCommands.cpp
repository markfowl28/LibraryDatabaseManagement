#include "BookCommands.h"
#include <iostream>
#include <sqlite3.h>
#include "Statement.h"
#include <string>
#include <istream>
#include <stdexcept>
#include <limits>
#include <ios>

bool executeStatement(Statement& stmt) {
    int rc = sqlite3_step(stmt.get());
    if (rc == SQLITE_DONE) return true;

    return false;
}

bool updateAvailability(sqlite3* db, int id, bool available) {
    Statement stmt(
        db,
        "UPDATE books SET available = ? WHERE id = ?"
    );

    sqlite3_bind_int(stmt.get(), 1, available ? 1 : 0);
    sqlite3_bind_int(stmt.get(), 2, id);

    return executeStatement(stmt);
}

bool updateTitle(sqlite3* db, int id, const std::string& newTitle) {
    Statement stmt(
        db,
        "UPDATE books SET title = ? WHERE id = ?"
    );

    sqlite3_bind_text(
        stmt.get(),
        1,
        newTitle.c_str(),
        -1,
        SQLITE_TRANSIENT
    );
    sqlite3_bind_int(stmt.get(), 2, id);

    return executeStatement(stmt);
}

bool updateAuthor(sqlite3* db, int id, const std::string& newAuthor) {
    Statement stmt(
        db,
        "UPDATE books SET author = ? WHERE id = ?"
    );

    sqlite3_bind_text(
        stmt.get(),
        1,
        newAuthor.c_str(),
        -1,
        SQLITE_TRANSIENT
    );
    sqlite3_bind_int(stmt.get(), 2, id);

    return executeStatement(stmt);
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

void editEntry(sqlite3* db) {
    int id;
    std::cout << "Enter book ID: ";
    std::cin >> id;

    int choice;
    std::cout << "\n";
    std::cout
        << "What would you like to update?\n"
        << "1) Title\n"
        << "2) Author\n"
        << "3) Availability\n"
        << "Choice: ";
    std::cin >> choice;
    std::cout << "\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool success = false;

    switch (choice) {
    case 1: {
        std::string title;
        std::cout << "Enter new title: ";
        std::getline(std::cin, title);
        success = updateTitle(db, id, title);
        break;
    }
    case 2: {
        std::string author;
        std::cout << "Enter new author: ";
        std::getline(std::cin, author);
        success = updateAuthor(db, id, author);
        break;
    }
    case 3: {
        int available;
        std::cout << "Available (1 = yes, 0 = no): ";
        std::cin >> available;
        success = updateAvailability(db, id, available != 0);
        break;
    }
    default:
        std::cout << "Invalid selection.\n";
        return;
    }

    if (!success) {
        std::cout << "Update failed or no matching record found.\n";
    }
    else {
        std::cout << "Update Successful!\n";
    }
}

void removeEntry(sqlite3* db) {
    Statement stmt(
        db,
        "DELETE FROM BOOKS WHERE title = ? COLLATE NOCASE"
    );

    std::string book;
    std::cout << "\n";
    std::cout << "Please enter the title you wish to remove: ";
    std::getline(std::cin >> std::ws, book);

    if (sqlite3_bind_text(stmt.get(), 1,book.c_str(), -1,SQLITE_TRANSIENT) != SQLITE_OK)
        throw std::runtime_error("Failed to bind title");

    if (executeStatement(stmt)) {
        std::cout << book << " removed successfully!\n";
        std::cout << "\n";
    }
    else {
        throw std::runtime_error("Failed to remove entry");
    }
}



