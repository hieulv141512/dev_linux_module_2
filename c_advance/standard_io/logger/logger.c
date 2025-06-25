#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char* levelStrings[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
    "WARNING", "NOTICE", "INFO", "DEBUG"
};

static const char* getFilenameFromPath(const char* path) {
    const char* filename = strrchr(path, '/');
    if (filename == NULL) {
        return path;
    }
    return filename + 1;
}

Logger* loggerInit(const char* filename, LogLevel minLevel) {
    Logger* logger = (Logger*)malloc(sizeof(Logger));
    if (logger == NULL) {
        fprintf(stderr, "LOGGER ERROR: Failed to allocate memory for Logger instance.\n");
        return NULL;
    }

    logger->currentLogLevel = minLevel;
    logger->logFile = NULL;

    if (filename != NULL) {
        logger->logFile = fopen(filename, "a");
        if (logger->logFile == NULL) {
            fprintf(stderr, "LOGGER ERROR: Could not open log file '%s' for new logger.\n", filename);
            free(logger);
            return NULL;
        }
    }

    return logger;
}

void setLogLevel(Logger* logger, LogLevel level) {
    if (logger == NULL) return;
    logger->currentLogLevel = level;
}

void destroyLogger(Logger* logger) {
    if (logger == NULL) return;

    if (logger->logFile != NULL) {
        fclose(logger->logFile);
        logger->logFile = NULL;
    }
    free(logger);
}

void loggerLog(Logger* logger, LogLevel level, const char* file, int line, const char* format, ...) {
    if (logger == NULL) {
        fprintf(stderr, "LOGGER ERROR: logger can't be NULL.\n");
        return;
    }

    if (level > logger->currentLogLevel) {
        return;
    }

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timestampBuffer[32];
    strftime(timestampBuffer, sizeof(timestampBuffer), "%Y-%m-%d %H:%M:%S", t);

    const char* shortFile = getFilenameFromPath(file);

    char logMessageBuffer[65536];
    long offset = 0;

    offset = snprintf(logMessageBuffer, sizeof(logMessageBuffer),
                      "[%s] [%s] [%s:%d] - ",
                      timestampBuffer,
                      levelStrings[level],
                      shortFile,
                      line);

    if (offset < 0 || offset >= (long)sizeof(logMessageBuffer)) {
        offset = sizeof(logMessageBuffer) - 1;
    }

    va_list args;
    va_start(args, format);
    vsnprintf(logMessageBuffer + offset, sizeof(logMessageBuffer) - offset, format, args);
    va_end(args);

    if (level <= LOG_ERROR) {
        fprintf(stderr, "%s\n", logMessageBuffer);
    } else {
        fprintf(stdout, "%s\n", logMessageBuffer);
    }

    fflush(stdout);
    fflush(stderr);

    if (logger->logFile != NULL) {
        fprintf(logger->logFile, "%s\n", logMessageBuffer);
        fflush(logger->logFile);
    }
}