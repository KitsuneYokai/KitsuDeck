SET(SOURCES screens/ui_Home.c
    screens/ui_SettingsView.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_deckimg_png.c
    images/ui_img_gear_png.c
    images/ui_img_b2_png.c
    images/ui_img_macro_icon_png.c)

add_library(ui ${SOURCES})
