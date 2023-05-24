#include "ScreenMessages.h"
#include "utils/Screen.h"

// error message for sd card error
void errorSD()
{
    gfx->setCursor(0, 0);
    gfx->setTextSize(5);
    gfx->println("SD Card Error\n");
    gfx->setTextSize(2);
    gfx->println("Hello, I'm KitsuDeck!");
    gfx->println("I can't find your SD Card :(");
    gfx->println("Please insert one and restart me\n\n\n");
    gfx->setTextSize(3);
    gfx->println("Quick Tip:\n");
    gfx->setTextSize(2);
    gfx->println("    The SD Card should be formatted as FAT32");
    gfx->println("    and shouldn't be larger than 8GB.");
    gfx->println("    Also, make sure that the SD Card is");
    gfx->println("    inserted correctly.\n");
    gfx->println("    If you still can't get it to work,");
    gfx->println("    please contact me on Discord!             - KitsuneYokai#7746\n\n\n\n");
    gfx->setCursor(0, gfx->height() - 20);
    gfx->println("I'll give you 60 seconds until I explode! :D");
    //  wait for a while
    delay(60000);
    // restart the device
    ESP.restart();
}

// error message when

void errorSettings()
{
    gfx->setCursor(0, 0);
    gfx->setTextSize(5);
    gfx->println("Settings Error\n");
    gfx->setTextSize(2);
    gfx->println("Hello, I'm KitsuDeck!");
    gfx->println("I can't find your settings file :(");
    gfx->println("Please make sure that you have a settings.json file,\n");
    gfx->println("and check if the format is valid.\n\n");
    gfx->setTextSize(3);
    gfx->println("Quick Tip:\n");
    gfx->setTextSize(2);
    gfx->println("    The settings file should be located in the root");
    gfx->println("    directory of your SD Card and should be named");
    gfx->println("    settings.json.\n");
    gfx->println("    If you still can't get it to work,");
    gfx->println("    please contact me on Discord!             - KitsuneYokai#7746\n\n\n\n");
    gfx->setCursor(0, gfx->height() - 20);
    gfx->println("You have 60 seconds until I expose your Browser History! :D");
    //  wait for a while
    delay(60000);
    // restart the device
    ESP.restart();
}

void errorWiFi()
{
    gfx->setCursor(0, 0);
    gfx->setTextSize(5);
    gfx->println("WiFi Error\n");
    gfx->setTextSize(2);
    gfx->println("Hello, I'm KitsuDeck!");
    gfx->println("I can't connect to your WiFi network :(");
    gfx->println("Please make sure that your Wifi criterials are");
    gfx->println("correct and try again.\n\n");
    gfx->setTextSize(3);
    gfx->println("Quick Tip:\n");
    gfx->setTextSize(2);
    gfx->println("    Make sure that your WiFi network is in Range");
    gfx->println("    and that you have the correct password.\n");
    gfx->println("    If you still can't get it to work,");
    gfx->println("    please contact me on Discord!             - KitsuneYokai#7746\n\n\n\n");
}
