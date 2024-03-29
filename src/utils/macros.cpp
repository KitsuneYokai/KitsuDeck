#include "macros.h"
#include "Database/Sqlite.h"
#include "../ui/ui.h"

#include "WebServer/WebServer.h"

void ui_event_macroBtnClickEvent(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_PRESSED)
    {
        String *user_data = static_cast<String *>(target->user_data);
        if (user_data != nullptr)
        {
            String macro_id = *user_data;
            String macro_action_quary = "SELECT action FROM macros WHERE id = " + macro_id;
            DynamicJsonDocument macro_action = selectOne(macro_action_quary.c_str());
            // add a field to the macro_action json object, so that the websocket knows that this is a macro
            macro_action["event"] = "MACRO_INVOKED";
            sendWebsocketMessage(macro_action.as<String>());
            Serial.println("User invoked: " + macro_id);
        }
    }
}

// helper functions for the macros (load macros, ... )
void loadKitsuDeckMacros()
{
    Serial.println("loading macros");
    // clear all items from ui_DeckCol
    lv_obj_clean(ui_DeckCol);

    // get the first 20 macros from the database and display them, order the query by layout_position and add a offset
    String offset = String(lv_slider_get_value(ui_DeckNavSlider) * 20);

    String macro_quarry = "SELECT layout_position, image, id FROM macros WHERE NOT layout_position=0 AND layout_position > " + offset + " ORDER BY layout_position ASC LIMIT 20";
    DynamicJsonDocument macros = selectAll(macro_quarry.c_str());

    // fill macros into ui_DeckCol, by getting the layout_position value from macros, and setting the macros at the right position
    for (int i = 0; i < 20; i++)
    {
        bool macro_exists = false;
        // go through the macros array and get the layout_position value
        for (int j = 0; j < macros.size(); j++)
        {
            int layout_position = macros[j]["layout_position"].as<int>() - (lv_slider_get_value(ui_DeckNavSlider) * 20);
            if (layout_position == i + 1)
            {
                // create a new macro button
                lv_obj_t *macro = lv_imgbtn_create(ui_DeckCol);
                lv_obj_set_size(macro, 100, 100);

                // set the image of the macro button
                String image = macros[j]["image"];
                if (image == "null")
                {
                    // Serial.println("image is null, setting default image");
                    lv_img_set_src(macro, &ui_img_macro_icon_png);
                }
                else
                {
                    String macro_image_quary = "SELECT name FROM macro_images WHERE id = " + image;
                    DynamicJsonDocument macro_image_path = selectOne(macro_image_quary.c_str());
                    String imagePath = "S:/images/macro_images/" + macro_image_path["name"].as<String>();
                    lv_img_set_src(macro, imagePath.c_str());
                }
                // TODO: btn click event
                lv_obj_set_user_data(macro, (void *)new String(macros[j]["id"].as<String>()));
                lv_obj_add_event_cb(macro, ui_event_macroBtnClickEvent, LV_EVENT_ALL, NULL);
                macro_exists = true;
                break;
            }
        }
        if (!macro_exists)
        {
            // creating an empty canvas with the same size as the macro (100x100) to keep the layout
            lv_obj_t *macro_spacer = lv_canvas_create(ui_DeckCol);
            lv_obj_set_size(macro_spacer, 100, 100);
        }
    }
}
