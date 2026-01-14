#pragma once
#include <sqlite3.h>
#include "Statement.h"
#include <string>

bool executeStatement(Statement&);

bool updateAvailability(sqlite3*, int, bool);

bool updateTitle(sqlite3*, int, const std::string&);

bool updateAuthor(sqlite3*, int, const std::string&);

void createEntry(sqlite3*);

void editEntry(sqlite3*);

void removeEntry(sqlite3*);




