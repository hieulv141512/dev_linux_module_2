#include "../inc/uart_channel_base.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Uart channel implementations
int uartSend(void* instance, const uint8_t* data, size_t length) {
    UartChannel* uart = (UartChannel*)instance;
    if (!uart || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    if (uart->txLength + length > sizeof(uart->txBuffer)) {
        return COMM_ERROR_BUFFER_FULL;
    }

    // Simulate UART transmission
    memcpy(uart->txBuffer + uart->txLength, data, length);
    uart->txLength += length;
    printf("UART: Sent %zu bytes successfully.\n", length);

    return (int)length;
}
int uartReceive(void * instance, uint8_t* buffer, size_t bufferLength, size_t* receiveLength) {
    UartChannel* uart = (UartChannel*)instance;
    if (!uart || !buffer || !receiveLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    // Simulate UART receipt
    size_t copy_length = uart->rxLength < bufferLength ? uart->rxLength : bufferLength;
    memcpy(buffer, uart->rxBuffer, copy_length);
    *receiveLength = copy_length;
    printf("UART: Received %zu bytes successfully.\n", copy_length);

    return (int)copy_length;
}

Channel* createUartChannel() {
    UartChannel* uart = (UartChannel*)malloc(sizeof(UartChannel));
    if (uart == NULL) {
        fprintf(stderr, "Failed to allocate memmory for UART channel instance. \n");
        return NULL;
    }
    memset(uart, 0, sizeof(UartChannel));

    Channel* channel = (Channel*)malloc(sizeof(Channel));
    if (channel == NULL) {
        fprintf(stderr, "Failed to allocate memmory for channel instance. \n");
        return NULL;
    }

    channel->instance = &uart;
    channel->send = uartSend;
    channel->receive = uartReceive;

    return channel;
}