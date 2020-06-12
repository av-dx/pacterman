.PHONY = pacman all clean

pacman: main Vector2D Entity Map Player
	g++ -std=c++11 -pthread main.o Vector2D.o Entity.o Map.o Player.o -o pacman

main: main.cpp
	g++ -std=c++11 -pthread -c main.cpp

Vector2D: Vector2D.cpp
	g++ -c Vector2D.cpp

Entity: Entity.cpp
	g++ -c Entity.cpp

Map: Map.cpp
	g++ -c Map.cpp

Player: Player.cpp
	g++ -c Player.cpp

all : pacman Vector2D.o Entity.o main.o

clean:
	\rm *.o