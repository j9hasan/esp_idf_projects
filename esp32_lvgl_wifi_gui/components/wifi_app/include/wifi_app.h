#ifndef __WIFI_MNG_H__
#define __WIFI_MNG_H__
/* INCLUDES */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include <time.h>
#include <sys/time.h>
#include "esp_attr.h"
#include "esp_sleep.h"
#include "esp_sntp.h"

/* DEFINES */
#define WIFI_MAX_RETRY 2
#define DEFAULT_SCAN_LIST_SIZE 7
#define WIFI_SSID_BUFFER_SIZE 32

/* VARS */
static char wifi_dd_list[WIFI_SSID_BUFFER_SIZE * 20] = {0};
static char wifi_ssid_dd[WIFI_SSID_BUFFER_SIZE] = {0};
// char ssid_name[WIFI_SSID_BUFFER_SIZE * 7] = "";

/* SNTP */

/* FUNCTION PROTOTYPES */

#ifdef __cplusplus
extern "C"
{
#endif
    /* FUNCTION PROTOTYPES FOR USING IN C FILE */
    void wifi_scan_task(void *pvParameters);
    void wifi_conn_task(void *pvParameters);
    void wifi_init_sta(void);
    void Set_SystemTime_SNTP();
    void Get_current_date_time();
#ifdef __cplusplus
}
#endif
#endif
