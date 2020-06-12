.PHONY = pacman all clean

pacman: main.o Vector2D.o Entity.o Map.o
	g++ -std=c++11 -pthread main.o Vector2D.o Entity.o Map.o -o pacman

main.o: main.cpp
	g++ -std=c++11 -pthread -c main.cpp

Vector2D.o: Vector2D.cpp
	g++ -c Vector2D.cpp

Entity.o: Entity.cpp
	g++ -c Entity.cpp

Map.o: Map.cpp
	g++ -c Map.cpp

all : pacman Vector2D.o Entity.o main.o

clean:
	\rm *.o