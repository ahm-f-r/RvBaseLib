CXX       := g++
CXXFLAGS  := -pedantic-errors -Wall -Wextra -Werror -std=c++20
LDFLAGS   := -L/usr/lib -lstdc++ -lm
ROOT_DIR  := $(PWD)
BUILD_DIR := $(ROOT_DIR)/build
OBJ_DIR   := $(BUILD_DIR)/objects
BIN_DIR   := $(BUILD_DIR)/bin
INC_DIR   := $(ROOT_DIR)/source/include
DFN_DIR   := $(ROOT_DIR)/source/defines
#TARGET    := Passed as an argument from cmd prompt.
INCLUDE   := -I$(INC_DIR) -I$(DFN_DIR)
SRC       := $(wildcard $(ROOT_DIR)/source/main/*.cpp) $(wildcard $(ROOT_DIR)/source/tests/sanity_tests/*.cpp)

OBJECTS   := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

all: build $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS) -I$(INC_DIR)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

info:
	@echo "[*] Root dir:        ${ROOT_DIR}    "
	@echo "[*] Application dir: ${BIN_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
                       