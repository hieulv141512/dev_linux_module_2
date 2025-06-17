# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/music_player.c \
       $(SRC_DIR)/player_state.c \
       main.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Output executable
TARGET = musicPlayer

# Build rules
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
