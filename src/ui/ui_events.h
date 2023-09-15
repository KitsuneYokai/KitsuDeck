// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: KitsuDeck

#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void initKitsudeck(lv_event_t * e);
void DeckNavSliderReleased(lv_event_t * e);
void DeckNavSliderValueChange(lv_event_t * e);
void ScanWifiSsid(lv_event_t * e);
void SaveWifiSettings(lv_event_t * e);
void TestWifiSettings(lv_event_t * e);
void SaveComputerAuthSettings(lv_event_t * e);
void setSettingsBrightnessArkValue(lv_event_t * e);
void saveSettingsBrightnessArkValue(lv_event_t * e);
void saveClockUtcSettings(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
