#include <sqlite3.h>
#include <SD.h>
#include <Arduino.h>

#include "Sqlite.h"

// define database file name
#define DATABASE_FILE "/kitsuDeck.db"

sqlite3 *db;

int openDb(const char *filename, sqlite3 **db)
{
    int rc = sqlite3_open(filename, db);
    if (rc)
    {
        Serial.printf("Can't open database: %s \n", sqlite3_errmsg(*db));
        return rc;
    }
    return rc;
}

char *zErrMsg = 0;
int db_exec(const char *sql)
{
    int rc = SQLITE_OK;

    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        Serial.println("Error: failed to open database.");
        return rc;
    }

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        Serial.printf("SQL error: %s \n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    return rc;
}

void initDatabase()
{
    sqlite3_initialize();

    if (!SD.exists(DATABASE_FILE))
    {
        Serial.println("Creating new database file.");
        File file = SD.open(DATABASE_FILE, FILE_WRITE);
        file.close();
    }

    int rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        Serial.println("Error: failed to open database.");
        // TODO: add error screen here
        return;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS makros (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, key TEXT, description TEXT, type int, picture blob, invoked int DEFAULT 0)";
    rc = db_exec(sql);
    if (rc != SQLITE_OK)
    {
        Serial.println("Error: failed to create table.");
        // TODO: add error screen here
        return;
    }

    sqlite3_close(db);
}