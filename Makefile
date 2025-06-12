CXX = clang++
EIGEN_DIR = external/eigen
CXXFLAGS = -std=c++17 -Wall -Iinclude -I$(EIGEN_DIR) -MMD -MP

SRC_FILES = $(shell find src -name '*.cpp')
OBJ_FILES = $(patsubst src/%.cpp,build/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

BIN = ml_toolkit

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP_FILES)

clean:
	rm -rf build $(BIN)

