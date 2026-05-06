CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# List of all source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# List of all object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Target executable
TARGET = $(BIN_DIR)/bank

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test:
	$(CXX) $(CXXFLAGS) tests/test.cpp $(SRC_DIR)/account.cpp $(SRC_DIR)/savingsAccount.cpp $(SRC_DIR)/checkingAccount.cpp $(SRC_DIR)/bank.cpp $(SRC_DIR)/utils.cpp -o $(BIN_DIR)/test_bank

.PHONY: all clean test