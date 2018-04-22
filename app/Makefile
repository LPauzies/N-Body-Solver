CXX = g++
FLAGS = -fopenmp -std=c++11
BODY = body
ERR = error
GRAP = graphics
READ = reader
GNU = gnuplot
BIN = bin
SRC = $(wildcard *.cpp)
HEAD = $(wildcard *.hpp)
OBJ = $(SRC:.cpp=.o)

OUTPUT = prog

all: $(OBJ)
	$(CXX) $(FLAGS) -o $(BIN)/$(OUTPUT) $(BIN)/$^

$(OBJ): %.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $(BIN)/$@

run: $(BIN)/$(OUTPUT)
	./$(BIN)/$(OUTPUT)

clean:
	rm -rf *.o *.gch $(BODY)/*.o $(ERR)/*.o $(GRAP)/*.o $(READ)/*.o $(GNU)/*.o $(BODY)/*.gch $(ERR)/*.gch $(GRAP)/*.gch $(READ)/*.gch $(GNU)/*.gch $(BIN)/*.o
cleanall: clean
	rm -rf $(BIN)/$(OUTPUT)
