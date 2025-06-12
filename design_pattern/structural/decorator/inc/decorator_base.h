#ifndef DECORATOR_BASE_H
#define DECORATOR_BASE_H
#include "channel.h"

// Base interface for decorators
typedef struct {
    Channel* wrapped;
} DecoratorBase;

#endif // DECORATOR_BASE_H