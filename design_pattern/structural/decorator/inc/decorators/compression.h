#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "../decorator_base.h"

// Structure Compression Decorator
typedef struct {
    DecoratorBase base;
} CompressionDecorator;

int compressionSend(void* instance, const uint8_t* data, size_t length);
int compressionReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
CompressionDecorator* createCompressionDecorator(Channel* wrapped);
void freeCompressionDecorator(CompressionDecorator* decorator);

#endif // COMPRESSION_H