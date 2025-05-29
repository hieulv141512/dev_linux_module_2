#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdint.h>

#define BAUD_RATE_1200      1200
#define BAUD_RATE_9600      9600
#define BAUD_RATE_115200    115200
#define PARITY_NONE         0
#define PARITY_ODD          1
#define PARITY_EVEN         2
#define STOP_BITS_1         1
#define STOP_BITS_2         2
#define DATA_BITS_8         8
#define DATA_BITS_9         9

// UART Configuration Structure
typedef struct {
    uint32_t baudRate;
    uint8_t parity;
    uint8_t stopBits;
    uint8_t dataBits;
} UART_Config;

// UART Builder Structure
typedef struct UART_Builder {
    UART_Config config;
    struct UART_Builder* (*setBaudRate)(struct UART_Builder*, uint32_t);
    struct UART_Builder* (*setParity)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setStopBits)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setDataBits)(struct UART_Builder*, uint8_t);
    UART_Config (*build)(struct UART_Builder*);
} UART_Builder;

// Function to initialize the Builder
UART_Builder UART_Builder_Init();

void printUartConfig(const UART_Builder* builder);

#endif // UART_BUILDER_H
    