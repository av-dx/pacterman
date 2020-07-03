.PHONY = pacterman all clean

pacterman: main.o Vector2D.o Entity.o Map.o Player.o Ghost.o
	g++ -std=c++11 -pthread main.o Vector2D.o Entity.o Map.o Player.o Ghost.o GhostState.o -o pacterman

main.o: main.cpp
	g++ -std=c++11 -pthread -c main.cpp

Vector2D.o: Vector2D.cpp
	g++ -c Vector2D.cpp

Entity.o: Entity.cpp
	g++ -c Entity.cpp

Map.o: Map.cpp Map.h
	g++ -c Map.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Ghost.o: Ghost.cpp GhostState.o
	g++ -c Ghost.cpp

GhostState.o: GhostState.cpp
	g++ -c GhostState.cpp

all : pacterman Vector2D.o Entity.o main.o

clean:
	\rm *.o