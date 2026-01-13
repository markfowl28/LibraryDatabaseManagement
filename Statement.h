#pragma once
#include <sqlite3.h>
#include <string>

class Statement {
public:
    // Constructor: prepares the SQL statement
    Statement(sqlite3* db, const std::string& sql);

    // Destructor: finalizes the statement (RAII)
    ~Statement();

    // Disable copying (statements have unique ownership)
    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    // Access the underlying sqlite statement
    sqlite3_stmt* get() const;

private:
    sqlite3_stmt* stmt_;
};
