/***
 * First Demo program using Snomann Ingenior's code.
 * Uses FreeRTOS Task
 * Blink LED and send UART message every tenth blink cycle.
 * Al Baeza
 * Januuary 22, 2024
 * February 8, 2025
 * Added blinking Led for Pico2 W RP2350
 * First working project using SDK 2.1.0 for Pico2
 *
 * Features tested with this project:
 * Pico SDK 2.1.0
 * SDK support for Pico2 W RP2350
 * FreeRTOS with support for RP2350
 * UART
 * Internal LED blinking with CYW43
 */

// Make sure the correct version of FreeRTOS with support for RP2350 is used.
// Link:
// https://github.com/raspberrypi/FreeRTOS-Kernel/tree/main/portable/ThirdParty/GCC/RP2350_ARM_NTZ

// Useful commands serial interface commands:
// minicom -b 115200 -o -D /dev/ttyUSB0
// minicom -b 115200 -o -D /dev/ttyACM0


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

// Define task handles
TaskHandle_t myTask1Handle = NULL;

#define LED_PIN    25
#define LED_DLY_MS 250

// If using Pico instead of Pico W
//#define PICO_SELECTED

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

// This is the only task for this test project.
// Blink LED and send UART message every tenth blink cycle
void myTask1 (void *p) {
   int count = 0;
   while(1) {
      if (count % 10 == 0) {
         printf("Hello, world. : %d\r\n", count);   // print once every tenth blink cycle
      }
      count++;  // increment counter
      

           // Pico
#ifdef PICO_SELECTED
      gpio_put(LED_PIN, 1);
      vTaskDelay(LED_DLY_MS);  //  delay
      gpio_put(LED_PIN, 0);
      vTaskDelay(LED_DLY_MS);  // delay
#else
      // Pico W
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
      vTaskDelay(LED_DLY_MS);  //  delay
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
      vTaskDelay(LED_DLY_MS);  //  delay
#endif
   }
}

/***
 * Main
 * @return
 */
int main( void )
{
    //Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);

    // Pico W
#ifdef CYW43_WL_GPIO_LED_PIN
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
#endif

    // Pico
#ifdef PICO_SELECTED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
#endif

    printf("GO\n");

    //Start tasks and scheduler
    const char *rtos_name = "FreeRTOS";
    printf("Starting %s on core 0:\n", rtos_name);
	
    xTaskCreate(myTask1, "MainThread", 500, NULL, TASK_PRIORITY, &myTask1Handle);
	
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
	
    // Forever loop
    while(1) {
           //
    }


    return 0;
}
