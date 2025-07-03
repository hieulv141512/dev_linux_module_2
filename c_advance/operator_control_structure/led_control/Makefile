# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source & object folder
OBJ_DIR = obj

# Source files
SRCS = led_driver.c main.c
	
# Object files
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter %,$(SRCS))) \
       $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out %,$(SRCS)))

# Target output
TARGET = LedDriver

# --- Phony targets ---
.PHONY: all clean run

# build rules
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
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