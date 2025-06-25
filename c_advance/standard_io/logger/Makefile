# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

# Source files
SRCS = logger.c main.c

# Directories
OBJ_DIR = obj

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Output executable
TARGET = Logger

# --- Phony targets ---
.PHONY: all clean run

# build rules
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Build successful: $(TARGET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.log
	@echo "Cleaned up build files."

run: $(TARGET)
	./$(TARGET)