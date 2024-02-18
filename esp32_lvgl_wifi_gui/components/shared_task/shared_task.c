#include <stdio.h>
#include "shared_task.h"

/* sample task create
    xTaskCreatePinnedToCore(
        myTask,          // Task function
        "MyTask",        // Task name
        TASK_STACK_SIZE, // Stack size
        NULL,            // Task parameters (if any)
        TASK_PRIORITY,               // Task priority
        task_handle,            // Task handle (optional, can be NULL)
        TASK_CORE               // Core to pin the task to (0 or 1)
    );
    */