#include "Database.h"
#include <stdexcept>
#include <sqlite3.h>

Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database");
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* Database::get() const {
    return db;
}


