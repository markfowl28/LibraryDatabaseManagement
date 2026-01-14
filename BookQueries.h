#pragma once
#include <sqlite3.h>
#include "Statement.h"

bool printResults(Statement&);

void lookupEntry(sqlite3*);

void viewAllEntries(sqlite3*);




