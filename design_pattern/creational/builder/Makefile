# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/uart_builder.c \
       main.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS))) \
       $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/%,$(SRCS)))

# Output executable
TARGET = UartBuilder

# --- Phony targets ---
.PHONY: all clean run

# build rules
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Build successful: $(TARGET)"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned up build files."

run: $(TARGET)
	./$(TARGET)