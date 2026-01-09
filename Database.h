#pragma once
#include <sqlite3.h>
#include <string>

class Database {
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

public:
    explicit Database(const std::string& filename);
    ~Database();

    sqlite3* get() const;

private:
    sqlite3* db = nullptr;
};




