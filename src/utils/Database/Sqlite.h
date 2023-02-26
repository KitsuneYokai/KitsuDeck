#ifndef _SQLITE_H_
#define _SQLITE_H_

#include <sqlite3.h>

int openDb(const char *filename, sqlite3 **db);
int db_exec(const char *sql);
String selectOne(const char *query);
String selectAll(const char *query);

void initDatabase();

#endif