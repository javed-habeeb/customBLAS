# Compiler settings
CXX      := g++
# Added your optimizations (-Os), section-splitting, and C++23. 
# Added -MMD -MP for automatic header dependency tracking.
CXXFLAGS := -Wall -Wextra -Os -std=c++23 -fdata-sections -ffunction-sections -Iinclude -MMD -MP
LDFLAGS  := -Wl,--gc-sections

# Directories
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
BIN_DIR   := bin

# Target executable
TARGET := $(BIN_DIR)/main

# Find all source files and map them to object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# Generate a list of dependency files (.d) matching the object files
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link object files into the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile individual source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the generated dependency files (tells Make about header changes)
-include $(DEPS)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

