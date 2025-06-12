#ifndef CRC_H
#define CRC_H

#include "../decorator_base.h"

// Structure CRC Decorator
typedef struct {
    DecoratorBase base;
} CrcDecorator;

int crcSend(void* instance, const uint8_t* data, size_t length);
int crcReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
CrcDecorator* createCrcDecorator(Channel* wrapped);
void freeCrcDecorator(CrcDecorator* decorator);

#endif // CRC_H