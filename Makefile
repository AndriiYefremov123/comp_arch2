CXX = g++
CXXFLAGS = -Wall -Iinclude
SRC = src/calculator.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = calculator
LIB = libcalc.a

all: $(LIB) $(TARGET)

$(LIB): src/calculator.o
	ar rcs $@ $^

$(TARGET): src/main.o $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(LIB) $(TARGET)
