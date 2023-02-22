#ifndef _SQLITE_H_
#define _SQLITE_H_

#include <sqlite3.h>

int openDb(const char *filename, sqlite3 **db);
int db_exec(sqlite3 *db, const char *sql);
void initDatabase();

#endif