#include "SearchDatabaseHeader.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include "Statement.h"
#include <string>
#include <vector>
#include <istream>

struct User {
	int id;
	std::string title;
	std::string author;
	int available;
};

bool printResults(Statement& stmt) {
	bool found = false;

	while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
		found = true;
		User user{
			sqlite3_column_int(stmt.get(), 0),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1)),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 2)),
			sqlite3_column_int(stmt.get(), 3),
		};

		std::cout << "\n";
		std::cout
			<< "ID: " << user.id << "  "
			<< "Title: " << user.title << "  "
			<< "Author: " << user.author << "  "
			<< "Available: " << user.available
			<< "\n";
	}
	std::cout << "\n";
	return found;
}


void lookupEntry(sqlite3* db) {
	Statement stmt(
		db,
		"SELECT id, title, author, available FROM BOOKS WHERE title = ? COLLATE NOCASE"
	);

	std::string book;
	std::cout << "\n";
	std::cout << "Please enter the title: ";
	std::getline(std::cin >> std::ws, book);

	sqlite3_bind_text(
		stmt.get(),
		1,
		book.c_str(),
		-1,
		SQLITE_TRANSIENT
	);

	if (!printResults(stmt)) {
		std::cout << "No books found matching that title.\n";
		std::cout << "\n";
	}
}


void viewAllEntries(sqlite3* db) {
	std::vector<User> users;

	std::string query = "SELECT id, title, author, available FROM BOOKS";
    Statement stmt(db, query);

	if (!printResults(stmt)) {
		std::cout << "Database is empty. \n";
		std::cout << "\n";
	}
}


