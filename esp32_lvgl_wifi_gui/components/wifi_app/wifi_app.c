
/*
    This example shows how to scan for available set of APs.
*/
#include "wifi_app.h"
#include "shared_task.h"
#include "lvgl.h"
#include "ui.h"
#include "helper_func.h"

/*WIFI DRIVER*/
TaskHandle_t wifi_scan_task_handle = NULL, wifi_connect_task_handle = NULL, get_date_time_task_handle = NULL;
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;
/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
/*event bits*/
EventBits_t bits;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

static int s_retry_num = 1;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    wifi_event_sta_connected_t wesc;
    wifi_event_sta_disconnected_t wesd;

    static const char *TAG = "WIFI EVENT HANDLER";

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "event id: WIFI_EVENT_STA_START ");
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
    {
        ESP_LOGI(TAG, "WIFI connected to SSID: %s, BSSID: " MACSTR ", channel %d, authmode %u", wesc.ssid, MAC2STR(wesc.bssid), wesc.channel, wesc.authmode);

        // create_notif_panel("Wifi", "WIFI Connected", true);

        // vTaskDelay(700 / portTICK_PERIOD_MS);

        // notif_panel_del();
        // set conn bit
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        // create_notif_panel("Wifi", "WIFI not connected", false);
        // vTaskDelay(500 / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "WIFI disconnected from %s, reason %d, rssi %d", wesd.ssid, wesd.reason, wesd.rssi);

        if (s_retry_num < WIFI_MAX_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retrying to connect to the AP");
        }
        else
        {
            ESP_LOGI(TAG, "connection failed. setting:s_wifi_event_group = WIFI_FAIL_BIT ");
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG, "connect to the AP fail");

        // notif_msg_update("Connection failed.");

        // vTaskDelay(700 / portTICK_PERIOD_MS);

        // notif_panel_del();
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));

        // Assuming IPv4, 16 characters maximum
        char ip_str[16];

        // Format IP address and store it in the char array
        sprintf(ip_str, IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;

        // create_notif_panel("Wifi", "WIFI connected.", false);

        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void)
{
    const char *TAG = "WIFI STA INIT";

    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    bits = xEventGroupWaitBits(s_wifi_event_group,
                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                               pdFALSE,
                               pdFALSE,
                               portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT)
    {
        // ESP_LOGI(TAG, "connected to ap SSID:%s password:%s", EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
        ESP_LOGI(TAG, "connected bit 1");

        create_notif_panel("Wifi", "WIFI connected.", false);

        // vTaskDelay(700 / portTICK_PERIOD_MS);

        // notif_panel_del();
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        // ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s", EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
        ESP_LOGI(TAG, "connected bit 0");

        create_notif_panel("Wifi", "WIFI not connected.", false);

        // vTaskDelay(700 / portTICK_PERIOD_MS);

        // notif_panel_del();
    }
    else
    {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
    /* The event will not be processed after unregister */
    // ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    // ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    // vEventGroupDelete(s_wifi_event_group);
}

void wifi_conn_task(void *pvParameters)
{

    create_notif_panel("Wifi", "Connecting...", true);

    /*take ssid from dd*/
    lv_dropdown_get_selected_str(ui_wifi_ssid_dd, wifi_ssid_dd, WIFI_SSID_BUFFER_SIZE);

    /*type converting ssid*/
    uint8_t temp_ssid[32] = "";
    uint8_t temp_pass[64] = "";
    memcpy(temp_ssid, wifi_ssid_dd, 32);
    memcpy(temp_pass, lv_textarea_get_text(ui_wifi_pass_ta), 64);
    // ESP_LOGI(TAG, "temp_ssid: %s",temp_ssid);
    // ESP_LOGI(TAG, "temp_pass: %s",temp_pass);
    // ESP_LOGI(TAG, "wifi connect task");

    ESP_ERROR_CHECK(esp_wifi_stop());
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = "",
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };

    u8cpy(wifi_config.sta.ssid, temp_ssid);
    u8cpy(wifi_config.sta.password, temp_pass);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    vTaskDelay(500 / portTICK_PERIOD_MS);
    notif_panel_del();

    wifi_connect_task_handle = NULL;
    vTaskDelete(wifi_connect_task_handle);
}

/* Initialize Wi-Fi as sta and set scan method */
void wifi_scan_task(void *pvParameters)
{
    static const char *TAG = "wifi scan";
    ESP_LOGI(TAG, "wifi AP scan");

    create_notif_panel("Wifi", "Scanning...", true);

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "scan started");

    notif_msg_update("Scanning...");
    vTaskDelay(500 / portTICK_PERIOD_MS);

    esp_wifi_scan_start(NULL, true);

    notif_msg_update("Scan finished.");
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // ESP_LOGI(TAG, "Max AP number ap_info can hold = %u", number);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(TAG, "Total APs scanned = %u, actual AP number ap_info holds = %u", ap_count, number);

    // lv_label_set_text_fmt(ui_notifyPanellabel, "AP found %u\nsetting dropdown", ap_count);
    // clear all bits

    memset(wifi_dd_list, 0, sizeof(wifi_dd_list));
    for (int i = 0; i < number; i++)
    {
        // ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
        // ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
        // ESP_LOGI(TAG, "Channel \t\t%d", ap_info[i].primary);
        strncat(wifi_dd_list, (char *)ap_info[i].ssid, WIFI_SSID_BUFFER_SIZE);
        if (i < (number - 1))
        {
            strcat(wifi_dd_list, "\n");
        }
    }
    // ESP_LOGI(TAG, "WiFi DD List:\n%s", wifi_dd_list);
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, 100 / portMAX_DELAY))
    {
        lv_dropdown_set_options(ui_wifi_ssid_dd, wifi_dd_list);
        xSemaphoreGive(xGuiSemaphore);
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);

    notif_panel_del();

    wifi_scan_task_handle = NULL;
    vTaskDelete(wifi_scan_task_handle);
}

// char Current_Date_Time[100];
void display_time(void *pvParameters)
{
    while (1)
    {
        Get_current_date_time();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void time_sync_notification_cb(struct timeval *tv)
{
    const char *TAG = "time ev notification";
    ESP_LOGI(TAG, "Notification of a time synchronization event");
    xTaskCreatePinnedToCore(display_time,
                            "display time",
                            GET_DATE_TIME_TASK_STACK_SIZE,
                            NULL,
                            GET_DATE_TIME_TASK_PRIORITY,
                            &get_date_time_task_handle,
                            GET_DATE_TIME_TASK_CORE);
}

void Get_current_date_time()
{
    // const char *TAG = "getDateTime";
    char strftime_buf[10];
    time_t now;
    struct tm timeinfo;
    // Set timezone to Bangladesh Standard Time (UTC+6:00)
    setenv("TZ", "UTC -6", 1);
    tzset();
    time(&now);
    localtime_r(&now, &timeinfo);
    // strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%H:%M:%S", &timeinfo);
    // ESP_LOGI(TAG, "The current date/time in DHAKA is: %s", strftime_buf);
    // strcpy(date_time, strftime_buf);
    // lv_label_set_text_fmt(ui_timeLabel, "%s", strftime_buf);
    // lv_label_set_text_fmt(ui_timeLabelUiAgentArmory, "%s", strftime_buf);
}

static void initialize_sntp(void)
{
    const char *TAG = "initialize_sntp";
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_SMOOTH
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
#endif
    sntp_init();
}
static void obtain_time(void)
{
    const char *TAG = "obtain_time";
    initialize_sntp();
    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    time(&now);
    localtime_r(&now, &timeinfo);
}
void Set_SystemTime_SNTP()
{
    const char *TAG = "Set_SystemTime_SNTP";
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900))
    {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time();
        // update 'now' variable with current time
        time(&now);
    }
}
