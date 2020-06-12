.PHONY = all clean

all : pacman Vector2D Entity main

pacman: main Vector2D Entity
	g++ -std=c++11 -pthread main.o Vector2D.o Entity.o -o pacman

Vector2D: Vector2D.cpp
	g++ -c Vector2D.cpp

main: main.cpp
	g++ -std=c++11 -pthread -c main.cpp

Entity: Entity.cpp
	g++ -c Entity.cpp

clean:
	\rm *.o