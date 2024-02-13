#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define BUTTON_PIN 27
#define DEBOUNCE_TIME_MS 200

SemaphoreHandle_t xSemaphore = NULL;

static void IRAM_ATTR button_isr_handler(void *arg)
{
    // arg is a pointer to the GPIO number
    int gpio_num = (int)arg;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
}

void button_task(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY))
        {
            // vTaskDelay(DEBOUNCE_TIME_MS / portTICK_PERIOD_MS);

            // Check the button state after debounce
            if (gpio_get_level(BUTTON_PIN) == 0)
            {
                printf("Pressed\n");
            }
        }
    }
}

void app_main()
{
    // Create a binary semaphore to handle button events
    xSemaphore = xSemaphoreCreateBinary();

    // Configure button GPIO as input
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&io_conf);

    // Install ISR service with default configuration
    gpio_install_isr_service(0);

    // Hook ISR handler to the button pin
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, (void *)BUTTON_PIN);

    // Create a task to handle button events
    xTaskCreate(button_task, "button_task", configMINIMAL_STACK_SIZE * 3, NULL, 10, NULL);
}
