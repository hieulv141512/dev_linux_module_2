#include "inc/uart_builder.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    // Initialize the Builder
    UART_Builder builder = UART_Builder_Init();
    printUartConfig(&builder);

    // Configure UART using the Builder
    UART_Config config = builder
        .setBaudRate(&builder, BAUD_RATE_115200)
        ->setParity(&builder, PARITY_EVEN)
        ->setStopBits(&builder, STOP_BITS_2)
        ->setDataBits(&builder, DATA_BITS_9)
        ->build(&builder);

    printUartConfig(&builder);

    return 0;
}