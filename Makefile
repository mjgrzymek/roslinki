CPPFLAGS = -O3 -Wall -Wextra -Wshadow
LIBS=-lsfml-graphics -lsfml-window -lsfml-system 

compilation:
	g++ -o main main.cpp $(LIBS)
