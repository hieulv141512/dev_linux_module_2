#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    COMM_SUCCESS,
    COMM_ERROR_INVALID_PARAM,
    COMM_ERROR_BUFFER_FULL,
    COMM_ERROR_CRC_MISMATCH,
    COMM_ERROR_ENCRYPTION_FAIL,
    COMM_ERROR_COMPRESSION_FAIL,
} ErrorCodes;

// Common interface for all channels
typedef struct Channel {
    void* instance;
    int (*send)(void* instance, const uint8_t* data, size_t length);
    int (*receive)(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receiveLength);
} Channel;

#endif // CHANNEL_H