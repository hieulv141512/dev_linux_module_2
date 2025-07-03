#include "led_driver.h"
#include <stdio.h>
#include <assert.h>

const size_t LED_PIXEL_COUNT = 10;

void printHexPixelInfo(size_t index, uint32_t value) {
    printf("Hexa value at index %zu: %#08x\n", index, value);
}

int main() {

    printf("Initialize LED strip with %zu pixels...\n", LED_PIXEL_COUNT);
    if (ledInit(LED_PIXEL_COUNT) != 0) {
        fprintf(stderr, "Can't initialize LED strip.\n");
        return 1;
    }
    size_t numPixels = ledGetPixelCount();
    printf("Number of pixels: %zu\n", numPixels);
    assert(numPixels == LED_PIXEL_COUNT);

    printf("Check whether buffer are initialized as 0. \n");
    const uint32_t* buffer = ledGetBuffer();
    if (buffer == NULL) {
        fprintf(stderr, "Initialized buffer can't be NULL.\n");
        ledShutdown();
        return 1;
    }

    int allZeros = 1;
    for (int i = 0; i < numPixels; i++) {
        if (buffer[i] != 0x00000000) {
            allZeros = 0;
            break;
        }
    }

    printf("All pixels are set to zeros: %s\n", (allZeros == 1) ? "YES": "NO");

    printf("Set colors to pixels.\n");
    ledSetPixelColor(0, 255, 0, 0);
    ledSetPixelColor(9, 0, 0, 255);
    ledSetPixelColor(4, 255, 255, 255);

    printf("Check Hexa value of pixels.\n");
    printHexPixelInfo(0, buffer[0]);
    printHexPixelInfo(9, buffer[9]);
    printHexPixelInfo(4, buffer[4]);

    printf("Fill all pixels into green.\n");
    ledFill(0, 255, 0);

    printf("Check whether all pixels are green. \n");
    int allGreen = 1;
    for (int i = 0; i < numPixels; i++) {
        if (buffer[i] != 0x00FF0000) {
            allGreen = 0;
            break;
        }
    }

    printf("All pixels are set to green: %s\n", (allGreen == 1) ? "YES": "NO");

    printf("Free memory.\n");
    ledShutdown();

    return 0;
}