#ifndef _CLOCK_H
#define _CLOCK_H
#include <Arduino.h>

void initClockTimer();
void initSNTP();
int timeToSeconds(const std::string &timeStr);
void setClockTimezone();
void wait_for_sntp_sync(void *param);
void stopSNTP();

#endif