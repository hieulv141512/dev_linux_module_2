# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source & object folder
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/humidity/humidity_sensor.c \
		$(SRC_DIR)/light/light_sensor.c \
		$(SRC_DIR)/pressure/pressure_sensor.c \
		$(SRC_DIR)/temperature/temperature_sensor.c \
		$(SRC_DIR)/sensor_factory/sensor_factory.c \
		$(SRC_DIR)/sensor_factory/sensor.c \
		main.c
	
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS))) \
       $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/%,$(SRCS)))

# Target output
TARGET = SensorFactory

# --- Phony targets ---
.PHONY: all clean run

# build rules
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Build successful: $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned up build files."

run: $(TARGET)
	./$(TARGET)