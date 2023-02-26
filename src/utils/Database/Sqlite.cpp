#include <sqlite3.h>
#include <SD.h>
#include <Arduino.h>

#include "Sqlite.h"

// define database file name
#define DATABASE_FILE "/kitsuDeck.db"

sqlite3 *db;
// TODO: PSRAM buffer for storing the entire request body

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

String selectOne(const char *query)
{
    int rc = SQLITE_OK;
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to open database");
        return "Failed to open database";
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to prepare statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "Failed to prepare statement";
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        log_e("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "No rows returned";
    }

    // TODO: still afraid of the ArduinoJson
    String result = "{";
    for (int i = 0; i < sqlite3_column_count(stmt); i++)
    {
        if (i > 0)
        {
            result += ",";
        }
        result += "\"";
        result += sqlite3_column_name(stmt, i);
        result += "\":\"";
        result += (char *)sqlite3_column_text(stmt, i);
        result += "\"";
    }
    result += "}";
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

String selectAll(const char *query)
{
    int rc = SQLITE_OK;
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to open database");
        return "Failed to open database";
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to prepare statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "Failed to prepare statement";
    }

    String result = "[";
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result += "{";
        for (int i = 0; i < sqlite3_column_count(stmt); i++)
        {
            if (i > 0)
            {
                result += ",";
            }
            result += "\"";
            result += sqlite3_column_name(stmt, i);
            result += "\":\"";
            result += (char *)sqlite3_column_text(stmt, i);
            result += "\"";
        }
        result += "},";
    }
    if (result.endsWith(","))
    {
        result = result.substring(0, result.length() - 1); // Remove the trailing comma
    }
    result += "]";
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
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