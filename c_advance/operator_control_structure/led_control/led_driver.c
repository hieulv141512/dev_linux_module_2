#include "led_driver.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint32_t* globalLedBuffer = NULL;
static size_t globalNumLedPixels = 0;

int ledInit(size_t num_pixels) {
    if (num_pixels == 0) {
        fprintf(stderr, "LED ERROR: num_pixel can't be 0.\n");
        return -1;
    }

    if (globalLedBuffer != NULL) {
        fprintf(stderr, "LED ERROR: Led driver already initialized. Freeing and re-create.\n");
        ledShutdown();
    }

    globalLedBuffer = (uint32_t*)malloc(num_pixels * sizeof(uint32_t));
    if (globalLedBuffer == NULL) {
        fprintf(stderr, "LED ERROR: Failed to allocate global led buffer. \n");
        globalNumLedPixels = 0;
        return -1;
    }

    memset(globalLedBuffer, 0, num_pixels * sizeof(uint32_t));
    globalNumLedPixels = num_pixels;

    return 0;
}

void ledShutdown() {
    if (globalLedBuffer != NULL) {
        free(globalLedBuffer);
        globalLedBuffer = NULL;
    }
    globalNumLedPixels = 0;
}

void ledSetPixelColor(size_t index, uint8_t red, uint8_t green, uint8_t blue) {
    if (globalLedBuffer == NULL || index >= globalNumLedPixels) {
        return;
    }

    uint32_t colorValue = 0x00000000;
    colorValue |= ((uint32_t)green << 16);
    colorValue |= ((uint32_t)red << 8);
    colorValue |= (uint32_t)blue;

    globalLedBuffer[index] = colorValue;

}

void ledFill(uint8_t red, uint8_t green, uint8_t blue) {
    if (globalLedBuffer == NULL || globalNumLedPixels == 0) {
        return;
    }

    uint32_t colorValue = 0x00000000;
    colorValue |= ((uint32_t)green << 16);
    colorValue |= ((uint32_t)red << 8);
    colorValue |= (uint32_t)blue;

    for(int i = 0; i < globalNumLedPixels; i++) {
        globalLedBuffer[i] = colorValue;
    }
}

void ledClear() {
    ledFill(0, 0, 0);
}

const uint32_t* ledGetBuffer() {
    return globalLedBuffer;
}

size_t ledGetPixelCount() {
    return globalNumLedPixels;
}