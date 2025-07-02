# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -O2 -g

# Directories
SRC_DIR = src
INC_DIR = include
DEMO_DIR = demo
BUILD_DIR = build

# Output files
LIB_NAME = libtiny3d.a
LIB_PATH = $(BUILD_DIR)/$(LIB_NAME)
DEMO_BIN = $(BUILD_DIR)/demo

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Demo files
DEMO_SRC = $(DEMO_DIR)/main.c

# Default target
all: $(LIB_PATH) $(DEMO_BIN)

# Build static library
$(LIB_PATH): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build demo
$(DEMO_BIN): $(DEMO_SRC) $(LIB_PATH)
	$(CC) $(CFLAGS) $< -L$(BUILD_DIR) -ltiny3d -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Run demo
run: all
	./$(DEMO_BIN)

.PHONY: all clean run
