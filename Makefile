.POSIX:
.PHONY: all clean

BUILD_DIR := build
SRC_DIR := src

SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')
HDR := $(shell find $(SRC_DIR) -type f -name '*.hpp')
OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))

CXX := g++
CXXFLAGS := -Wall -Werror -c -g
LDFLAGS := $(shell pkg-config --cflags --libs sdl2)

all: network_sim

clean:
	rm network_sim
	rm -rf $(BUILD_DIR)

network_sim: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp $(HDR)
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -o $@ $<