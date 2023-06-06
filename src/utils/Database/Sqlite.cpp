#include <sqlite3.h>
#include <SD.h>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "Sqlite.h"

// define database file name
#define DATABASE_FILE "/kitsuDeck.db"

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

int db_exec(const char *sql)
{
    int rc = SQLITE_OK;
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db = NULL;
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

DynamicJsonDocument selectOne(const char *query)
{
    sqlite3 *db = NULL;
    int rc = SQLITE_OK;
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to open database");
        return DynamicJsonDocument(0);
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to prepare statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return DynamicJsonDocument(0);
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        log_e("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return DynamicJsonDocument(0);
    }

    DynamicJsonDocument doc(4096);
    JsonObject obj = doc.to<JsonObject>();
    for (int i = 0; i < sqlite3_column_count(stmt); i++)
    {
        const char *col_name = sqlite3_column_name(stmt, i);
        std::unique_ptr<char[]> col_name_copy(new char[strlen(col_name) + 1]);
        strcpy(col_name_copy.get(), col_name);
        if (sqlite3_column_type(stmt, i) == SQLITE_NULL)
        {
            obj[col_name_copy.get()] = nullptr;
        }
        else
        {
            obj[col_name_copy.get()] = (char *)sqlite3_column_text(stmt, i);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return doc;
}

DynamicJsonDocument selectAll(const char *query)
{
    sqlite3 *db = NULL;
    int rc = SQLITE_OK;
    char *errMsg = NULL;
    sqlite3_stmt *stmt = NULL;
    rc = openDb("/sd" DATABASE_FILE, &db);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to open database");
        return DynamicJsonDocument(0);
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_e("Failed to prepare statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return DynamicJsonDocument(0);
    }

    DynamicJsonDocument result(2 * 4096);
    JsonArray data = result.to<JsonArray>();

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        JsonObject obj = data.createNestedObject();
        for (int i = 0; i < sqlite3_column_count(stmt); i++)
        {
            const char *col_name = sqlite3_column_name(stmt, i);
            char *col_name_copy = strdup(col_name); // create a copy of the column name string
            obj[col_name_copy] = (char *)sqlite3_column_text(stmt, i);
            free(col_name_copy);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

void initDatabase()
{
    sqlite3 *db = NULL;
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
    const char *sqlMacros = "CREATE TABLE IF NOT EXISTS macros(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, description TEXT, invoked INTEGER DEFAULT(0), action JSON, image INTEGER, layout_position INTEGER UNIQUE, CONSTRAINT macros_FK FOREIGN KEY(id) REFERENCES macro_images(id) ON DELETE SET NULL);";
    rc = db_exec(sqlMacros);
    const char *sqlMacroImages = "CREATE TABLE IF NOT EXISTS macro_images(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);";
    rc = db_exec(sqlMacroImages);

    sqlite3_close(db);
}