#include "../../inc/decorators/logging.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int loggingSend(void* instance, const uint8_t* data, size_t length) {
    LoggingDecorator* log = (LoggingDecorator*)instance;
    if (!log || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    char log_entry[256];
    snprintf(log_entry, sizeof(log_entry), "Sent %zu bytes: [%.16s...]", length, data);
    log->log_buffer = realloc(log->log_buffer, log->log_size + strlen(log_entry) + 1);
    strcpy(log->log_buffer + log->log_size, log_entry);
    log->log_size += strlen(log_entry) + 1;

    return log->base.wrapped->send(log->base.wrapped->instance, data, length);
}

int loggingReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    LoggingDecorator* log = (LoggingDecorator*)instance;
    int result = log->base.wrapped->receive(log->base.wrapped->instance, buffer, bufferLength, receivedLength);
    if (result >= 0) {
        char log_entry[256];
        snprintf(log_entry, sizeof(log_entry), "Received %zu bytes: [%.16s...]", *receivedLength, buffer);
        log->log_buffer = realloc(log->log_buffer, log->log_size + strlen(log_entry) + 1);
        strcpy(log->log_buffer + log->log_size, log_entry);
        log->log_size += strlen(log_entry) + 1;
    }

    return result;
}

LoggingDecorator* createLoggingDecorator(Channel* wrapped) {
    LoggingDecorator* log = (LoggingDecorator*)malloc(sizeof(LoggingDecorator));
    if (log == NULL) {
        fprintf(stderr, "Failed to allocate memory for Logging Decorator instance. \n");
        return NULL;
    }
    log->base.wrapped = wrapped;
    log->log_buffer = NULL;
    log->log_size = 0;

    log->base.wrapped->send = loggingSend;
    log->base.wrapped->receive = loggingReceive;
    log->base.wrapped->instance = log;

    return log;
}

void freeLoggingDecorator(LoggingDecorator* decorator){
    if (decorator != NULL) {
        free(decorator->base.wrapped);
        free(decorator);
    }
}