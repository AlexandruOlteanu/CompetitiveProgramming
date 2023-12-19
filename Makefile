# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Name of your executable
TARGET = main_exe

# Source files
SRC = main.cpp

# Rule for making the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

# Rule for cleaning the project
clean:
	rm -f $(TARGET)
