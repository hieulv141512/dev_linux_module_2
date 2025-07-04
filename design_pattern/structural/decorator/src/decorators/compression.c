#include "../../inc/decorators/compression.h"
#include <stdlib.h>
#include <stdio.h>


int compressionSend(void* instance, const uint8_t* data, size_t length) {
    CompressionDecorator* comp = (CompressionDecorator*)instance;
    if (!comp || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }
    uint8_t* compressed = malloc(length * 2);
    size_t outPos = 0;
    for (size_t i = 0; i < length;) {
        uint8_t count = 1;
        while (i + count < length && data[i] == data[i + count] && count < 255) count++;
        compressed[outPos++] = data[i];
        compressed[outPos++] = count;
        i += count;
    }
    int result = comp->base.wrapped->send(comp->base.wrapped->instance, compressed, outPos);
    printf("Compression: Compressed data successfully.\n");
    free(compressed);

    return result > 0 ? length : result;

}

int compressionReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    CompressionDecorator* comp = (CompressionDecorator*)instance;
    uint8_t* tempBuffer = malloc(bufferLength * 2);
    size_t tempReceived;
    int result = comp->base.wrapped->receive(comp->base.wrapped->instance, tempBuffer, bufferLength * 2, &tempReceived);
    if (result < 0) {
        free(tempBuffer);
        *receivedLength = 0;
        return result;
    }
    size_t outPos = 0;
    for (size_t i = 0; i < tempReceived && outPos < bufferLength; i += 2) {
        uint8_t value = tempBuffer[i];
        uint8_t count = tempBuffer[i + 1];
        for (uint8_t j = 0; j < count && outPos < bufferLength; j++) {
            buffer[outPos++] = value;
        }
    }
    *receivedLength = outPos;
    printf("Compression: Decompressed data successfully.\n");
    free(tempBuffer);

    return (int)outPos;
}

CompressionDecorator* createCompressionDecorator(Channel* wrapped) {
    CompressionDecorator* comp = (CompressionDecorator*)malloc(sizeof(CompressionDecorator));
    if (comp == NULL) {
        fprintf(stderr, "Failed to allocate memory for Compression Decorator instance. \n");
        return NULL;
    }
    comp->base.wrapped = wrapped;
    comp->base.wrapped->send = compressionSend;
    comp->base.wrapped->receive = compressionReceive;
    comp->base.wrapped->instance = comp;

    return comp;
}

void freeCompressionDecorator(CompressionDecorator* decorator) {
    if (decorator != NULL) {
        free(decorator->base.wrapped);
        free(decorator);
    }
}