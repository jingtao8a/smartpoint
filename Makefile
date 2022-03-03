CPP      = g++
OBJ      = main.o Counter.o
LINKOBJ  = main.o Counter.o
BIN      = smart_pointer.exe
INCLUDE = -I ./
.PHONY: all clean

all: $(BIN)

clean: 
	rm $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(INCLUDE)

Counter.o: Counter.cpp
	$(CPP) -c Counter.cpp -o Counter.o
