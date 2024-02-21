#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <queue.h>

static QueueHandle_t xQueue = NULL;

void vBlinkTask(void *pvParameters)
{
    const uint led_pin = PICO_DEFAULT_LED_PIN;
    uint uIValueToSend = 0;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while (1)
    {
        gpio_put(led_pin, true);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(pdMS_TO_TICKS(1000)); // FreeRTOS function to delay
        gpio_put(led_pin, false);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Convert milliseconds to ticks
    }
}

void usb_task(void *pvParameters)
{
    uint uIReceivedValue;

    while (true)
    {
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);

        if (uIReceivedValue == 1)
        {
            printf("LED is ON\n");
        };
        if (uIReceivedValue == 0)
        {
            printf("LED is OFF\n");
        };
    };
};

int main()
{
    stdio_init_all(); // Initialize standard I/O (if needed)

    xQueue = xQueueCreate(1, sizeof(uint));

    // Create the blink task
    xTaskCreate(vBlinkTask,       // Task function
                "Blink LED Task", // Name for debugging
                256,              // Stack size
                NULL,             // Parameters for task fn
                1,                // Priority
                NULL);            // Task handle

    xTaskCreate(usb_task,   // Task function
                "USB Task", // Name for debugging
                256,        // Stack size
                NULL,       // Parameters for task fn
                1,          // Priority
                NULL);      // Task handle

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // The scheduler takes over before this point. Main will never continue beyond here.
    for (;;)
        ;
}