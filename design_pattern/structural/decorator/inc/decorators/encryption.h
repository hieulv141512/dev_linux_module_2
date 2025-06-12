#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "../decorator_base.h"

// Structure Encryption Decorator
typedef struct {
    DecoratorBase base;
    uint8_t key;
} EncryptionDecorator;

int encryptionSend(void* instance, const uint8_t* data, size_t length);
int encryptionReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
EncryptionDecorator* createEncryptionDecorator(Channel* wrapped, uint8_t key);
void freeEncryptionDecorator(EncryptionDecorator* decorator);

#endif // ENCRYPTION_H