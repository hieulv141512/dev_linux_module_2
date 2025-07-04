#include "../../inc/decorators/encryption.h"
#include <stdlib.h>
#include <stdio.h>


int encryptionSend(void* instance, const uint8_t* data, size_t length) {
    EncryptionDecorator* enc = (EncryptionDecorator*)instance;
    uint8_t* encrypted = malloc(length);
    for (size_t i = 0; i < length; i++) {
        encrypted[i] = data[i] ^ enc->key;
    }
    int result = enc->base.wrapped->send(enc->base.wrapped->instance, encrypted, length);
    free(encrypted);
    printf("Encryption: Applied XOR encrytion with key: %02X.\n", enc->key);

    return result;
}

int encryptionReceive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    EncryptionDecorator* enc = (EncryptionDecorator*)instance;
    int result = enc->base.wrapped->receive(enc->base.wrapped->instance, buffer, bufferLength, receivedLength);
    if (result >= 0) {
        for (size_t i = 0; i < *receivedLength; i++) {
            buffer[i] ^= enc->key;
        }
    }
    printf("Encryption: Applied XOR decryption with key: %02X.\n", enc->key);

    return result;
}

EncryptionDecorator* createEncryptionDecorator(Channel* wrapped, uint8_t key) {
    EncryptionDecorator* enc = (EncryptionDecorator*)malloc(sizeof(EncryptionDecorator));
    if (enc == NULL) {
        fprintf(stderr, "Failed to allocate memory for Encryption Decorator instance. \n");
        return NULL;
    }
    enc->base.wrapped = wrapped;
    enc->key = key;

    enc->base.wrapped->send = encryptionSend;
    enc->base.wrapped->receive = encryptionReceive;
    enc->base.wrapped->instance = enc;

    return enc;
}

void freeEncryptionDecorator(EncryptionDecorator* decorator) {
    if (decorator != NULL) {
        free(decorator->base.wrapped);
        free(decorator);
    }
}