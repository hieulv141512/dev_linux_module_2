#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h>

int ledInit(size_t num_pixels);
void ledShutdown();
void ledSetPixelColor(size_t index, uint8_t red, uint8_t green, uint8_t blue);
void ledFill(uint8_t red, uint8_t green, uint8_t blue);
void ledClear();
const uint32_t* ledGetBuffer();
size_t ledGetPixelCount();

#endif  // LED_DRIVER_H