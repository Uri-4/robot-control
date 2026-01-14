#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024

enum MODE {
    INVALID = -1,
    OFF = 0,
    IDLE = 1,
    FOLLOW = 2,
    WALK = 3
};

void setup_uart() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    printf("\n\nSetup Complete\n");
}

MODE parse_command(const char * comm);

extern "C" void app_main() {
    uint8_t data[128];
    MODE active_mode = IDLE;
    setup_uart();
    printf("\nReady\n\n");
    while(1){
        int len = uart_read_bytes(UART_NUM, data, sizeof(data), 20/portTICK_PERIOD_MS);
        if (len > 0) {
            data[len] = 0;
            if (data[len-1] == '\n') data[len-1] = 0;
            if (data[len-2] == '\r') data[len-2] = 0;
            printf("\nComms Received, Got: %s\n", data);
            active_mode = parse_command((char *)data);
             //start activity
            printf("\nActive Status: %d %s\n\n", active_mode, data);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

MODE parse_command(const char * comm) {
    if (strcmp(comm, "IDLE") == 0) return IDLE;
    else if (strcmp(comm, "WALK") == 0) return WALK;
    else if (strcmp(comm, "FOLLOW") == 0) return FOLLOW;
    else if (strcmp(comm, "OFF") == 0) return OFF;
    else return INVALID;
};