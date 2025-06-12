#include "../../inc/decorators/crc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint16_t calculate_crc16(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xA001;
            else crc >>= 1;
        }
    }
    return crc;
}

int crcSend(void* instance, const uint8_t* data, size_t length){
    CrcDecorator* crc = (CrcDecorator*)instance;
    if (!crc || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* buffer = (uint8_t*)malloc(length + 2);
    memcpy(buffer, data, length);
    uint16_t crcValue = calculate_crc16(data, length);
    buffer[length] = crcValue & 0xFF;
    buffer[length + 1] = (crcValue >> 8) & 0xFF;
    int result = crc->base.wrapped->send(crc->base.wrapped->instance, buffer, length + 2);
    free(buffer);
    printf("CRC: Added CRC %02X \n", buffer[length]);

    return result > 2 ? result - 2 : result;
}

int crcReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength){
    CrcDecorator* crc = (CrcDecorator*)instance;
    if (!crc || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    size_t tempReceived;
    uint8_t* tempBuffer = malloc(bufferLength + 2);
    int result = crc->base.wrapped->receive(crc->base.wrapped->instance, tempBuffer, bufferLength + 2, &tempReceived);
    if (result < 0 || tempReceived < 2) {
        free(tempBuffer);
        *receivedLength = 0;
        return -1;
    }
    uint16_t receivedCrc = (tempBuffer[tempReceived - 1] << 8) | tempBuffer[tempReceived - 2];
    uint16_t calculatedCrc = calculate_crc16(tempBuffer, tempReceived - 2);
    if (receivedCrc != calculatedCrc) {
        free(tempBuffer);
        *receivedLength = 0;
        return COMM_ERROR_CRC_MISMATCH;
    }
    size_t dataLength = tempReceived - 2;
    memcpy(buffer, tempBuffer, dataLength);
    *receivedLength = dataLength;
    free(tempBuffer);
    printf("CRC: Received CRC: %02X. Calculated: %02X \n", receivedCrc, calculatedCrc);

    return (int)dataLength;
}

CrcDecorator* createCrcDecorator(Channel* wrapped){
    CrcDecorator* crc = (CrcDecorator*)malloc(sizeof(CrcDecorator));
    if (crc == NULL) {
        fprintf(stderr, "Failed to allocate memory for CRC Decorator instance. \n");
        return NULL;
    }

    crc->base.wrapped = wrapped;
    crc->base.wrapped->instance = crc;
    crc->base.wrapped->send = crcSend;
    crc->base.wrapped->receive = crcReceive;

    return crc;
}

void freeCrcDecorator(CrcDecorator* decorator){
    if (decorator != NULL) {
        free(decorator->base.wrapped);
        free(decorator);
    }
}