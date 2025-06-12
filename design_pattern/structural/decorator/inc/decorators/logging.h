#ifndef LOGGING_H
#define LOGGING_H

#include "../decorator_base.h"

// Structure Logging Decorator
typedef struct {
    DecoratorBase base;
    char* log_buffer;
    size_t log_size;
} LoggingDecorator;

int loggingSend(void* instance, const uint8_t* data, size_t length);
int loggingReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
LoggingDecorator* createLoggingDecorator(Channel* wrapped);
void freeLogDecorator(LoggingDecorator* decorator);

#endif // LOGGING_H