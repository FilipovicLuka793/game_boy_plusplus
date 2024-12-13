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
	@mkdir -p $(EXEC_DIR)
	$(CXX) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
