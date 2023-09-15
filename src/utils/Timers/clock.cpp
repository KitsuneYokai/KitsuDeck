#include "clock.h"
#include <iostream>

#include "../settings.h"
#include "../../ui/ui.h"
#include <ctime>
#include "esp_sntp.h"

void updateClock(lv_timer_t *timer) {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M", &timeinfo);
    lv_label_set_text(ui_Clock, time_str);
}

void initClockTimer() {
    lv_timer_create(updateClock, 1000, NULL);
}

void initSNTP() {
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

int timeToSeconds(const std::string& timeStr) {
    try {
        // Parse the input time string in the format "H:M"
        size_t pos = timeStr.find(":");
        if (pos == std::string::npos || pos == 0 || pos == timeStr.length() - 1) {
            throw std::invalid_argument("Invalid time format");
        }

        int hours = std::stoi(timeStr.substr(0, pos));
        int minutes = std::stoi(timeStr.substr(pos + 1));

        // Calculate the total seconds
        int seconds = hours * 3600 + minutes * 60;

        return seconds;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0; // Return 0 on error or invalid format
    }
}

void setClockTimezone() {
    struct timeval tv = {0};
    gettimeofday(&tv, NULL);
    //TODO: get settings UTC offset and set the timezone using the timeToSeconds function
    String utc = getSettings("utc");
    int utcSeconds = timeToSeconds(utc.c_str());
    tv.tv_sec += utcSeconds;
    settimeofday(&tv, NULL);
}

void wait_for_sntp_sync(void *param) {
    printf("wait_for_sntp_sync\n");
    const int max_retries = 15;
    const TickType_t retry_delay = 2000 / portTICK_PERIOD_MS;
    
    int retry = 0;
    sntp_sync_status_t sync_status;

    do {
        vTaskDelay(retry_delay);
        sync_status = sntp_get_sync_status();
        printf("SNTP Status: %d\n", sync_status);
    } while (sync_status != SNTP_SYNC_STATUS_COMPLETED && ++retry < max_retries);

    if (sync_status == SNTP_SYNC_STATUS_COMPLETED) {
        printf("Time synced successfully\n");
        setClockTimezone();
    } else {
        printf("SNTP synchronization failed\n");
        // Handle synchronization failure if needed
    }

    vTaskDelete(NULL); // Delete the task when done
}

void stopSNTP() {
    sntp_stop();
}