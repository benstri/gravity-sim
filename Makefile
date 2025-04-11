# Makefile for main.cpp

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Output executable
TARGET = main

# Source files
SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule for compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the target
clean:
	rm -f $(OBJ) $(TARGET)
