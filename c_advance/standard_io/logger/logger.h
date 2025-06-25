#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

// Define log levels
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFORMATIONAL,
    LOG_DEBUGGING
} LogLevel;

// Logger structure
typedef struct {
    LogLevel currentLogLevel;
    FILE* logFile;
} Logger;

// Function declarations
Logger* loggerInit(const char* filename, LogLevel minLevel);
void setLogLevel(Logger* logger, LogLevel level);
void destroyLogger(Logger* logger);

void loggerLog(Logger* logger, LogLevel level, const char* file, int line, const char* format, ...);

#define LOG_EMERG(loggerPtr, format, ...) loggerLog(loggerPtr, LOG_EMERGENCY, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_ALERT(loggerPtr, format, ...) loggerLog(loggerPtr, LOG_ALERT, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_CRIT(loggerPtr, format, ...)  loggerLog(loggerPtr, LOG_CRITICAL, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_ERROR(loggerPtr, format, ...) loggerLog(loggerPtr, LOG_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_WARN(loggerPtr, format, ...)  loggerLog(loggerPtr, LOG_WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_NOTICE(loggerPtr, format, ...) loggerLog(loggerPtr, LOG_NOTICE, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_INFO(loggerPtr, format, ...)  loggerLog(loggerPtr, LOG_INFORMATIONAL, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_DEBUG(loggerPtr, format, ...) loggerLog(loggerPtr, LOG_DEBUGGING, __FILE__, __LINE__, format, ##__VA_ARGS__)

#endif // LOGGER_H