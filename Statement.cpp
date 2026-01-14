#include "Statement.h"
#include <stdexcept>
#include <sqlite3.h>
#include <string>

Statement::Statement(sqlite3* db, const std::string& sql)
    : stmt_(nullptr)
{
    if (sqlite3_prepare_v2(
        db, sql.c_str(), -1, &stmt_, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare statement");
    }
}

Statement::~Statement() {
    if (stmt_) {
        sqlite3_finalize(stmt_);
    }
}

sqlite3_stmt* Statement::get() const {
    return stmt_;
}

