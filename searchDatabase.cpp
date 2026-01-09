#include "SearchDatabaseHeader.h"
#include <iostream>
#include <sqlite3.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	std::cout << "----------------------\n";
	return 0;
}

void lookupEntry() {}

void viewAllEntries() {
	sqlite3* db;
	char* errMsg = nullptr;
	int rc;

	rc = sqlite3_open("lms.db", &db);

	if (rc == SQLITE_OK) {
		std::cout << "Database opened successfully\n";
	}

	else if (rc != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
		return;
	}

	// Read data from the table
	const char* selectSQL = "SELECT * FROM BOOKS;";
	rc = sqlite3_exec(db, selectSQL, callback, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << "\n";
		sqlite3_free(errMsg);
	}

	sqlite3_close(db);
}
