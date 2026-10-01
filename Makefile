CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = matrix_ops

all: $(TARGET)

$(TARGET): matrix_ops.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) matrix_ops.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
