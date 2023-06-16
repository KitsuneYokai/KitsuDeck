#include <SD.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

#include "events.h"
#include "../../settings.h"
#include "../../Database/Sqlite.h"
#include "../../macros.h"

// EVENT_GET_MACRO_IMAGES event function
void handleGetMacroImagesEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(2 * 4096);
        response["event"] = EVENT_GET_MACRO_IMAGES;
        response["images"] = selectAll("SELECT * FROM macro_images");
        client->text(response.as<String>());
    }
}

// EVENT_DELETE_MACRO_IMAGE event function
void handleDeleteMacroImageEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_DELETE_MACRO_IMAGE;
        response["status"] = false;

        int id = json["image_id"];
        // get the image name from the database
        String image_quarry = "SELECT name FROM macro_images WHERE id = " + String(id);
        DynamicJsonDocument DbImage = selectOne(image_quarry.c_str());
        if (DbImage.isNull())
        {
            response["message"] = "Image not found";
            client->text(response.as<String>());
            return;
        }
        // sez all the macros that use this image to null
        String update_macro_image_quarry = "UPDATE macros SET image = null WHERE image = " + String(id);
        int update_macro_image = db_exec(update_macro_image_quarry.c_str());
        if (update_macro_image != SQLITE_DONE)
        {
            response["message"] = "Failed to update macros";
            client->text(response.as<String>());
        }
        // delete the image from the database
        String delete_image_quarry = "DELETE FROM macro_images WHERE id = " + String(id);
        int delete_macro_image = db_exec(delete_image_quarry.c_str());
        if (delete_macro_image == SQLITE_DONE)
        {
            // delete the image from the sd card
            SD.remove("/images/macro_images/" + DbImage["name"].as<String>());
            response["status"] = true;
            client->text(response.as<String>());
            loadKitsuDeckMacros();
        }
        else
        {
            response["message"] = "Failed to delete image from database";
            client->text(response.as<String>());
        }
    }
}

// EVENT_CREATE_MACRO event function
void handleCreateMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_CREATE_MACRO;
        response["status"] = false;

        String name = json["macro_name"];
        String description = json["macro_description"];
        String action = json["macro_action"];
        String image = json["macro_image_id"];

        // insert the macro into the database
        String insert_macro_quarry = "INSERT INTO macros (name, description, action, image) VALUES ('" + name + "', '" + description + "', '" + action + "', '" + image + "')";
        int insert_macro = db_exec(insert_macro_quarry.c_str());
        if (insert_macro == SQLITE_DONE)
        {
            response["status"] = true;
            client->text(response.as<String>());
        }
        else
        {
            response["message"] = "Failed to insert macro into database";
            client->text(response.as<String>());
        }
    }
}

// EVENT_EDIT_MACRO event function
void handleEditMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        String name = json["macro_name"];
        String description = json["macro_description"];
        String action = json["macro_action"];
        String image = json["macro_image_id"];
        String id = json["macro_id"];

        DynamicJsonDocument response(200);
        response["event"] = EVENT_EDIT_MACRO;
        response["status"] = false;

        // update the macro in the database
        String update_macro_quarry = "UPDATE macros SET name = '" + String(name) + "', description = '" + String(description) + "', action = '" + String(action) + "', image = '" + String(image) + "' WHERE id = " + String(id);
        int update_macro = db_exec(update_macro_quarry.c_str());
        if (update_macro == SQLITE_DONE)
        {
            response["status"] = true;
            client->text(response.as<String>());
            loadKitsuDeckMacros();
        }
        else
        {
            response["message"] = "Failed to update macro in database";
            client->text(response.as<String>());
        }
    }
}

// EVENT_DELETE_MACRO event function
void handleDeleteMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_DELETE_MACRO;
        response["status"] = false;

        String id = json["macro_id"];

        // delete the macro from the database
        String delete_macro_quarry = "DELETE FROM macros WHERE id = " + String(id);
        int delete_macro = db_exec(delete_macro_quarry.c_str());
        if (delete_macro == SQLITE_DONE)
        {
            response["status"] = true;
            client->text(response.as<String>());
            loadKitsuDeckMacros();
        }
        else
        {
            response["message"] = "Failed to delete macro from database";
            client->text(response.as<String>());
        }
    }
}

// EVENT_GET_MACROS event function
void handleGetMacrosEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        // get the number of macros in the database
        String count_macros_quarry = "SELECT COUNT(*) FROM macros";
        DynamicJsonDocument count_macros = selectOne(count_macros_quarry.c_str());
        // change the json COUNT(*) key to count as int
        count_macros["count"] = count_macros["COUNT(*)"].as<int>();
        count_macros.remove("COUNT(*)");
        // create a for loop for 20 macros at a time
        for (int i = 0; i < count_macros["count"].as<int>();)
        {
            Serial.println("sending macros" + String(i));
            // get the macro from the database
            String macro_quarry = "SELECT id, name, image, layout_position FROM macros LIMIT 20 OFFSET " + String(i);
            DynamicJsonDocument macros = selectAll(macro_quarry.c_str());
            DynamicJsonDocument response(2 * 4096);
            response["event"] = EVENT_GET_MACROS;
            response["count"] = count_macros["count"].as<int>();
            response["macros"] = macros;
            response["status"] = false;
            // if this is the last iteration of the loop set the status to true
            if (i + 20 >= count_macros["count"].as<int>())
            {
                response["status"] = true;
            }
            client->text(response.as<String>());
            i += 20;
        }
    }
}

// EVENT_GET_MACRO event function
void handleGetMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(2 * 4096);
        response["event"] = EVENT_GET_MACRO;
        response["status"] = false;

        int id = json["macro_id"];
        // get the macro from the database
        String macro_quarry = "SELECT id, name, description, action, image, invoked FROM macros WHERE id = " + String(id);
        DynamicJsonDocument macro = selectOne(macro_quarry.c_str());
        if (macro.isNull())
        {
            response["message"] = "Macro not found";
            client->text(response.as<String>());
            return;
        }
        response["macro"] = macro;
        response["status"] = true;
        client->text(response.as<String>());
    }
}

void handleUpdateMacroLayoutEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_UPDATE_MACRO_LAYOUT;

        // json variables
        String macro_id = json["macro_id"];
        String layout_position = json["layout_position"];
        // check if there is a macro in the layout position
        String macro_layout_check = "SELECT * FROM macros WHERE layout_position = '" + String(layout_position) + "'";
        DynamicJsonDocument macro_layout = selectOne(macro_layout_check.c_str());
        if (!macro_layout.isNull())
        {
            // if there is a macro in the layout position update it to null
            String old_macro_id = macro_layout["id"];
            String old_macro_update = "UPDATE macros SET layout_position = NULL WHERE id = '" + old_macro_id + "'";
            int old_macro = db_exec(old_macro_update.c_str());
            if (old_macro == SQLITE_DONE)
            {
                Serial.println("Old macro updated");
            }
        }
        // update the macro in the database to the new layout position
        String macro_quarry = "UPDATE macros SET layout_position = '" + String(layout_position) + "' WHERE id = " + String(macro_id);
        int macro = db_exec(macro_quarry.c_str());
        if (macro == SQLITE_DONE)
        {
            client->text(response.as<String>());
            loadKitsuDeckMacros();
        }
    }
}