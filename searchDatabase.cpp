#include "SearchDatabaseHeader.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include "Statement.h"
#include <string>
#include <vector>

struct User {
	int id;
	std::string title;
	std::string author;
	int available;
};

void lookupEntry(sqlite3* db) {
	
}

void viewAllEntries(sqlite3* db) {
	std::vector<User> users;

	std::string query = "SELECT id, author, title, available FROM BOOKS";
    Statement stmt(db, query);

	while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
		users.push_back({
			sqlite3_column_int(stmt.get(), 0),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1)),
			reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 2)),
			sqlite3_column_int(stmt.get(), 3),
			});
	}

	for (User& user : users) {
		std::cout
			<< "ID: " << user.id << "  "
			<< "Title: " << user.author << "  "
			<< "Author: " << user.title << "  "
			<< "Available: " << user.available << "  "
			<< "\n";
	}
}

