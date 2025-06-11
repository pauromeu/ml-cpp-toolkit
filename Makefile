CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_FILES = $(shell find src -name '*.cpp')
OBJ_FILES = $(patsubst src/%.cpp, build/%.o, $(SRC_FILES))

BIN = ml_toolkit

all: $(BIN)

$(BIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)

