#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define MAXIMUM_AP 20

static esp_err_t event_handler(void * ctx, system_event_t *event) {
  return ESP_OK;
}

static char *auth_mode_type(wifi_auth_mode_t auth_mode)
{
  char *types[] = {"OPEN", "WEP", "WPA PSK", "WPA2 PSK", "WPA WPA2 PSK", "MAX"};
  return types[auth_mode];
}

void wifiInit() {
  ESP_ERROR_CHECK(nvs_flash_init());
  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

  wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());

}

void app_main()
{
  wifiInit();

  wifi_scan_config_t scan_config = {
    .ssid = 0,
    .bssid = 0,
    .channel = 0,
    .show_hidden = true
  };

  ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

  wifi_ap_record_t wifi_records[MAXIMUM_AP];

  uint16_t max_records = MAXIMUM_AP;
  ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&max_records, wifi_records));

  printf("Number of Access Points Found: %d\n", max_records);
  printf("\n");
  printf("               SSID              | Channel | RSSI |   Authentication Mode \n");
  printf("***************************************************************\n");
  for (int i = 0; i < max_records; i++)
    printf("%32s | %7d | %4d | %12s\n", (char *)wifi_records[i].ssid, wifi_records[i].primary, wifi_records[i].rssi, auth_mode_type(wifi_records[i].authmode));
  printf("***************************************************************\n");
}