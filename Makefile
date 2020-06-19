.PHONY = pacman all clean

pacman: main Vector2D Entity Map Player Ghost
	g++ -std=c++11 -pthread main.o Vector2D.o Entity.o Map.o Player.o Ghost.o GhostState.o -o pacman

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

Ghost: Ghost.cpp GhostState
	g++ -c Ghost.cpp

GhostState: GhostState.cpp
	g++ -c GhostState.cpp

all : pacman Vector2D.o Entity.o main.o

clean:
	\rm *.o