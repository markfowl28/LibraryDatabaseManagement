#pragma once
#include <sqlite3.h>
#include "Statement.h"

bool executeStatement(Statement&);

void createEntry(sqlite3*);

void editEntry(sqlite3*);

void removeEntry(sqlite3*);



