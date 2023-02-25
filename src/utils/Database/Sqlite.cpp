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
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to open database");
        return rc;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to prepare statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return rc;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        log_e("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return rc;
    }

    sqlite3_finalize(stmt);
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

#define PSRAM_MAX_SIZE (7 * 1024 * 1024) // 7MB

char *getMakrosFromDatabase()
{
    // create a buffer for storing the sql query result
    uint8_t psram_buffer = 0;
    size_t psram_buffer_size = 0;

    char *jsonBuffer = (char *)ps_malloc(PSRAM_MAX_SIZE);
    if (jsonBuffer == NULL)
    {
        Serial.println("Error: unable to allocate memory for JSON buffer.");
        return NULL;
    }

    int rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        Serial.println("Error: failed to open database.");
        return NULL;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "SELECT * FROM makros", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        Serial.printf("SQL error: %s \n", sqlite3_errmsg(db));
        return NULL;
    }

    size_t jsonOffset = 0;
    jsonOffset += snprintf(&jsonBuffer[jsonOffset], PSRAM_MAX_SIZE - jsonOffset, "[");

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *sql = "CREATE TABLE IF NOT EXISTS makros (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, key TEXT, description TEXT, type int, picture blob, invoked int DEFAULT 0)";

        const char *id = (const char *)sqlite3_column_text(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        const char *description = (const char *)sqlite3_column_text(stmt, 3);

        size_t rowSize = snprintf(NULL, 0, "{\"id\":\"%s\",\"name\":\"%s\",\"value\":\"%s\"},", id, name, description);
        if (jsonOffset + rowSize >= PSRAM_MAX_SIZE)
        {
            Serial.println("Error: JSON buffer size exceeded.");
            break;
        }

        jsonOffset += snprintf(&jsonBuffer[jsonOffset], PSRAM_MAX_SIZE - jsonOffset, "{\"id\":\"%s\",\"name\":\"%s\",\"value\":\"%s\"},", id, name, description);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    jsonOffset--; // remove last comma
    jsonOffset += snprintf(&jsonBuffer[jsonOffset], PSRAM_MAX_SIZE - jsonOffset, "]");

    return jsonBuffer;
}