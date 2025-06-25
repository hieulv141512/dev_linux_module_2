#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Create logger & write log messages with LOG_INFO level
    Logger* logger = loggerInit("main.log", LOG_INFORMATIONAL);
    if (logger == NULL) {
        fprintf(stderr, "Failed to create logger. Exiting.\n");
        return EXIT_FAILURE;
    }
    LOG_INFO(logger, "Logger initialized with level INFO, logging to main.log");
    LOG_DEBUG(logger, "This debug message should NOT be visible by logger.");
    LOG_INFO(logger, "This is an informational message from logger.");
    LOG_ERROR(logger, "Error: Something went wrong in main application.");

    // Create other logger & try to write log message to console only
    Logger* otherLogger = loggerInit(NULL, LOG_WARNING);
    if (otherLogger == NULL) {
        fprintf(stderr, "Failed to create otherLogger. Proceeding with logger only.\n");
    } else {
        LOG_INFO(otherLogger, "Module logger initialized with level WARNING, logging ONLY to console.");
        LOG_DEBUG(otherLogger, "This debug message should NOT be visible by otherLogger.");
        LOG_WARN(otherLogger, "Warning: Specific module encountered a minor issue.");
        LOG_ERROR(otherLogger, "Error: Critical issue in module. This will be visible.");
    }

    printf("\n--- Changing logger level to DEBUG ---\n");
    setLogLevel(logger, LOG_DEBUGGING);
    LOG_INFO(logger, "Logger level changed to DEBUG. Now debug messages should be visible.");
    LOG_DEBUG(logger, "This debug message for logger SHOULD now be visible.");

    if (otherLogger != NULL) {
        printf("\n--- otherLogger still at WARNING level ---\n");
        LOG_INFO(otherLogger, "This INFO message for otherLogger should NOT be visible (still WARNING level).");
        LOG_DEBUG(otherLogger, "This DEBUG message for otherLogger should NOT be visible (still WARNING level).");
        LOG_CRIT(otherLogger, "otherLogger: CRITICAL message is always visible if level allows.");
    }

    printf("\nCheck 'main.log' for logger messages.\n");

    destroyLogger(logger);
    destroyLogger(otherLogger);
    
    return EXIT_SUCCESS;
}