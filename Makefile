# === Directories ===
INCLUDE_DIR = include
SRC_DIR = src
DEMO_DIR = demo
BUILD_DIR = build

# === Compiler ===
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I$(INCLUDE_DIR)

# === Sources and Objects ===
SRC_FILES = $(SRC_DIR)/canvas.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# === Demo Program ===
DEMO_SRC = $(DEMO_DIR)/main.c
DEMO_OBJ = $(BUILD_DIR)/main.o
DEMO_BIN = $(BUILD_DIR)/demo.exe

# === Targets ===
all: $(DEMO_BIN)

# Compile source files into build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c into build/
$(BUILD_DIR)/main.o: $(DEMO_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link everything into the demo binary
$(DEMO_BIN): $(OBJ_FILES) $(DEMO_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Run the program
run: $(DEMO_BIN)
	./$(DEMO_BIN)

# Clean the build
clean:
	rm -rf $(BUILD_DIR)/*.o $(DEMO_BIN) output.pgm

.PHONY: all run clean
