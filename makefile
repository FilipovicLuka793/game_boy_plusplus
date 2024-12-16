CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinc -I/usr/include/SDL2 -I/usr/include/SDL2_ttf

LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_ttf

SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXEC_DIR = $(BUILD_DIR)/bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

EXEC = $(EXEC_DIR)/emu

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	@mkdir -p $(EXEC_DIR)      # Create bin directory if it doesn't exist
	$(CXX) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)  # Link object files with SDL2 and SDL2_ttf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)       # Create obj directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@  # Compile source file into object file

clean:
	rm -rf $(BUILD_DIR)  # Remove the build directory

.PHONY: all clean
