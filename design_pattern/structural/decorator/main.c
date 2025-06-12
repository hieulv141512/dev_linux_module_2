#include "inc/channel.h"
#include "inc/uart_channel_base.h"
#include "inc/decorators/crc.h"
#include "inc/decorators/compression.h"
#include "inc/decorators/encryption.h"
#include "inc/decorators/logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    // Create a raw UART channel
    Channel* uartRaw = createUartChannel();
    
    // Decorate with processing layers
    LoggingDecorator* withLogging = createLoggingDecorator(uartRaw);
    EncryptionDecorator* withEncryption = createEncryptionDecorator(withLogging->base.wrapped, 0xAB);
    CompressionDecorator* withCompression = createCompressionDecorator(withEncryption->base.wrapped);
    CrcDecorator* withCrc = createCrcDecorator(withCompression->base.wrapped);

    // Test data
    uint8_t testData[] = {0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04};
    size_t testDataLength = sizeof(testData);

    printf("Original test data (%zu bytes): ", testDataLength);
    for (size_t i = 0; i < testDataLength; i++) {
        printf("%02X ", testData[i]);
    }
    printf("\n\n");

    // Send data through decorated channel
    printf("=== SENDING DATA ===\n");
    int sendResult = withCrc->base.wrapped->send(withCrc->base.wrapped->instance, testData, testDataLength);
    printf("Send result: %d\n\n", sendResult);

    // Receive data through decorated channel
    printf("=== RECEIVING DATA ===\n");
    uint8_t receiveBuffer[256];
    size_t receivedLength;
    int receiveResult = withCrc->base.wrapped->receive(withCrc->base.wrapped->instance, receiveBuffer, sizeof(receiveBuffer), &receivedLength);

    printf("Receive result: %d\n", receiveResult);
    if (receiveResult == COMM_SUCCESS && receivedLength > 0) {
        printf("Received data (%zu bytes): ", receivedLength);
        for (size_t i = 0; i < receivedLength; i++) {
            printf("%02X ", receiveBuffer[i]);
        }
        printf("\n");

        // Verify data integrity
        bool dataMatch = (receivedLength == testDataLength) && (memcmp(testData, receiveBuffer, testDataLength) == 0);
        printf("Data integrity check: %s\n", dataMatch ? "PASS" : "FAIL");
    }
    
    // Cleanup
    freeLogDecorator(withLogging);
    freeEncryptionDecorator(withEncryption);
    freeCompressionDecorator(withCompression);
    freeCrcDecorator(withCrc);
    
    return 0;
}