/***
 * First Demo program using Snomann Ingenior's code.
 * Uses FreeRTOS Task
 * Al Baeza
 * Januuary 22, 2024
 */


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

TaskHandle_t myTask1Handle = NULL;

void myTask1 (void *p) {
	int count = 0;
	while(1) {
		printf("Hello, world. : %d\r\n", count++);
		vTaskDelay(1000);  // 1 sec delay
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
    printf("GO\n");

    //Start tasks and scheduler
    const char *rtos_name = "FreeRTOS";
    printf("Starting %s on core 0:\n", rtos_name);
	
	xTaskCreate(myTask1, "MainThread", 500, NULL, TASK_PRIORITY, &myTask1Handle);
	
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
	
	while(1) {
		//
	}


    return 0;
}
