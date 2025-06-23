# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Wextra -Iinc


# Source files
SRCS = sensor_manager.c main.c

# Object files
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Output target
TARGET = sensor_manager

# build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Build successful: $(TARGET)"

	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up build files."

run: $(TARGET)
	./$(TARGET)