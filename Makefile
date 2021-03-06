
CXX = g++
CXXFLAGS = -Wall -g -pedantic

LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -pthread

SRC = $(shell find *.cpp)
OBJ = $(SRC:%.cpp=lib/%.o)
BIN = bin/main

all: $(BIN)

lib/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJ) $(BIN) *~ ./res/*~

run:
	./$(BIN)

