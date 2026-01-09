#include "SearchDatabaseHeader.h"
#include "Database.h"
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

void viewAllEntries(sqlite3* db) {
    const char* selectSQL = "SELECT * FROM BOOKS;";
    char* errMsg = nullptr;

    if (sqlite3_exec(db, selectSQL, callback, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

	sqlite3_close(db);
}

