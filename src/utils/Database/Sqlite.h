#ifndef _SQLITE_H_
#define _SQLITE_H_

#include <sqlite3.h>
#include <ArduinoJson.h>

int openDb(const char *filename, sqlite3 **db);
int db_exec(const char *sql);

DynamicJsonDocument selectOne(const char *query);
DynamicJsonDocument selectAll(const char *query);

void initDatabase();

#endif