# --- Configuration Variables ---
# The directory containing the source files
SRC_DIR := src

# The directory where build artifacts (like the executable) will be placed
BUILD_DIR := build

# The name of the final executable
TARGET_NAME := decryption

# The full path to the executable
TARGET := $(BUILD_DIR)/$(TARGET_NAME)

# The directory from which you want the program to run
RUN_DIR := . # '.' means the current (project root) directory

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# --- Build Rules ---

# Default target: builds the program
all: $(TARGET)

# Rule to create necessary directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile the source file
$(TARGET): $(SRC_DIR)/decryption.cpp $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# --- Run Rule ---

# Rule to run the program
run: $(TARGET)
	# Change directory to RUN_DIR and then execute the program
	cd $(RUN_DIR) && ./$(TARGET)

# --- Clean Rule ---

# Rule to clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)
