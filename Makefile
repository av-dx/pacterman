pacman: main.cpp Vector2D.cpp
	g++ -std=c++11 -pthread main.o Vector2D.o -o pacman

Vector2D.cpp:
	g++ -c Vector2D.cpp

main.cpp:
	g++ -std=c++11 -pthread -c main.cpp
