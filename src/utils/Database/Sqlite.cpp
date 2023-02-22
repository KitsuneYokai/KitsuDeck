#include <sqlite3.h>
#include <SD.h>
#include <Arduino.h>

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
int db_exec(sqlite3 *db, const char *sql)
{
    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        Serial.printf("SQL error: %s \n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
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

    char *errMsg = nullptr;
    int rc = sqlite3_open("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        Serial.println("Error: failed to open database.");
        // TODO: add error screen here
        return;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS makros (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, key TEXT, description TEXT, type int, invoked int, picture blob)";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        Serial.printf("Error: failed to create table: %s\n", errMsg);
        sqlite3_free(errMsg);
        return;
    }
    sqlite3_close(db);
}
