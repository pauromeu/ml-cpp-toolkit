CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = src/main.cpp
TARGET = hello

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)