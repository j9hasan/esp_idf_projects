#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t event_group;
const int got_temp = BIT0;
const int got_hum = BIT1;

void Get_Temperature(void *params)
{
  while (true)
  {
    xEventGroupSetBits(event_group, got_temp);
    printf("Temparture value received\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void Get_Humidity(void *params)
{
  while (true)
  {
    xEventGroupSetBits(event_group, got_hum);
    printf("Humidity value received\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void Sender(void *params)
{
  while (true)
  {
    xEventGroupWaitBits(event_group, got_temp | got_hum, true, true, portMAX_DELAY);
    printf("Sender: Received temperature and Humidity\n");
  }
}

void app_main(void)
{
  event_group = xEventGroupCreate();
  xTaskCreate(&Get_Temperature, "Get_Temperature", 2048, NULL, 1, NULL);
  xTaskCreate(&Get_Humidity, "Get_Humidity", 2048, NULL, 1, NULL);
  xTaskCreate(&Sender, "Sender", 2048, NULL, 1, NULL);
}

