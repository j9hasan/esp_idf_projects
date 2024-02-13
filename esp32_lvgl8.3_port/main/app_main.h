#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

#include "esp_system.h"
#include "esp_timer.h"
#include <esp_log.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_event.h"
#include "esp_wifi.h"
#include "driver/gpio.h"
#define DEBOUNCE_TIME_MS 200
#define LV_TICK_PERIOD_MS 10
extern SemaphoreHandle_t xSemaphore;
extern gpio_num_t BUTTON_PIN;
// #define TAG "app_main"
// static void guiTask(void *pvParameter);
#endif