SRC=texture.cpp window.cpp tile.cpp main.cpp map.cpp character.cpp movementmanager.cpp
OBJ=$(SRC:%.cpp=%.o)

LFLAGS=-lSDL2 -lSDL2_image
CURRDIR=`pwd`
CXX=g++ -std=c++11 -Wall -g

all: $(OBJ)
	$(CXX) $(OBJ) $(LFLAGS)

%.o: %.c
	$(CXX) $@ -c $< # if .cpp changed, recompile .o
clean: 
	rm -f *.o
