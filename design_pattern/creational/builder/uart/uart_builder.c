#include <stdio.h>
#include <stdlib.h>
#include "uart_builder.h"

// Function to set the baud rate
static UART_Builder* setBaudRate(UART_Builder* builder, uint32_t baudRate) {
    if (baudRate < BAUD_RATE_1200 || baudRate > BAUD_RATE_115200) {
        fprintf(stderr, "Error: Invalid baud rate. Must be between 1200 and 115200.\n");
        return builder;
    }
    builder->config.baudRate = baudRate;
    return builder;
}

// Function to set the parity
static UART_Builder* setParity(UART_Builder* builder, uint8_t parity) {
    if (parity > PARITY_EVEN) {
        fprintf(stderr, "Error: Invalid parity. Must be 0 (None), 1 (Odd) or 2 (Even).\n");
        return builder;
    }
    builder->config.parity = parity;
    return builder;
}

// Function to set the stop bits
static UART_Builder* setStopBits(UART_Builder* builder, uint8_t stopBits) {
    if (stopBits != STOP_BITS_1 && stopBits != STOP_BITS_2) {
        fprintf(stderr, "Error: Invalid stopBits. Must be 1 (1 Stop Bit), 2 (2 Stop Bits).\n");
        return builder;
    }
    builder->config.stopBits = stopBits;
    return builder;
}

// Function to set the data bits
static UART_Builder* setDataBits(UART_Builder* builder, uint8_t dataBits) {
    if (dataBits != DATA_BITS_8 && dataBits != DATA_BITS_9) {
        fprintf(stderr, "Error: Invalid dataBits. Must be 8 (8 Data Bits), 9 (9 Data Bits).\n");
        return builder;
    }
    builder->config.dataBits = dataBits;
    return builder;
}

// Function to build and return UART config
static UART_Config build(UART_Builder* builder) {
    return builder->config;
}

// Function to initialize the Builder
UART_Builder UART_Builder_Init(){
    UART_Builder builder;
    builder.config.baudRate = BAUD_RATE_9600;
    builder.config.parity = PARITY_NONE;
    builder.config.stopBits = STOP_BITS_1;
    builder.config.dataBits = DATA_BITS_8;
    builder.setBaudRate = setBaudRate;
    builder.setParity = setParity;
    builder.setStopBits = setStopBits;
    builder.setDataBits = setDataBits;
    builder.build = build;
    return builder;
}

// Function to print UART configurations
void printUartConfig(const UART_Builder* builder) {
    if (builder != NULL) {
        printf("\n---- UART Configurations ----\n");
        printf("UART baud rate: %d\n", builder->config.baudRate);
        printf("UART parity: %d\n", builder->config.parity);
        printf("UART stop bits: %d\n", builder->config.stopBits);
        printf("UART data bits: %d\n", builder->config.dataBits);
    }
}

