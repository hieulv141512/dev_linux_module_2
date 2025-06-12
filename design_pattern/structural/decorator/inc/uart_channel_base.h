#ifndef UART_CHANNEL_H
#define UART_CHANNEL_H

#include <stdint.h>
#include <stddef.h>
#include "channel.h"

// Structure for raw UART channel
typedef struct {
    uint8_t txBuffer[1024];
    size_t txLength;
    uint8_t rxBuffer[1024];
    size_t rxLength;
} UartChannel;

Channel* createUartChannel();
int uartSend(void* instance, const uint8_t* data, size_t length);
int uartReceive(void * instance, uint8_t* buffer, size_t bufferLength, size_t* receiveLength);

#endif // UART_CHANNEL_H