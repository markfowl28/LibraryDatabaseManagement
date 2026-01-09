#pragma once
#include <sqlite3.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName);

void lookupEntry();

void viewAllEntries(sqlite3*);


