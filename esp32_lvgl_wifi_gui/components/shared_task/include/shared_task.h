#ifndef __SHARED_TASK_H__
#define __SHARED_TASK_H__
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_timer.h"
#include <esp_log.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* gui task parameters */
#define GUI_TASK_STACK_SIZE 1024 * 5
#define GUI_TASK_PRIORITY 2
#define GUI_TASK_CORE 1

/*wifi task parameters*/
#define WIFI_TASK_PRIORITY 2
#define WIFI_SCAN_TASK_STACK_SIZE 5 * 1024
#define WIFI_CONNECT_TASK_STACK_SIZE 5 * 1024
#define WIFI_TASK_CORE 1

/*inv scan task parameters*/
#define INV_TASK_PRIORITY 6
#define INV_SCAN_TASK_STACK_SIZE 5 * 1024
#define INV_TASK_CORE 1

/*sntp get date time task parameters*/
#define GET_DATE_TIME_TASK_PRIORITY 5
#define GET_DATE_TIME_TASK_STACK_SIZE 2 * 1024
#define GET_DATE_TIME_TASK_CORE 1

/*rfid user mem task parameters*/
#define MEM_TASK_PRIORITY 5
#define MEM_TASK_STACK_SIZE 5 * 1024
#define MEM_TASK_CORE 1

#ifdef __cplusplus
extern "C"
{
#endif

    /*gui mutex*/
    extern SemaphoreHandle_t xGuiSemaphore;

    /*extern variables*/
    extern bool merge_on;
    extern bool filterOn;

    /* task handlers*/
    extern TaskHandle_t
        wifi_scan_task_handle,
        wifi_connect_task_handle,
        inventory_task_handle,
        get_date_time_task_handle,
        mem_task_handle,
        img_slider_task_handle,
        GUI_TASK_HANDLE;

    extern uint16_t row_, col_;

    // void createImgSlider(void *pvParameters);

#ifdef __cplusplus
}
#endif
#endif
