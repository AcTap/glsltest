CPP=g++
CPPFLAGS=-Wall -std=c++11
LDFLAGS=-lSDL2 -lGL -lGLU -lGLEW -lstdc++
OBJECTS=main.o painter.o
NAME=bin/glsltest

$(NAME) : $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

main.o : main.cpp painter.h
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c main.cpp

painter.o : painter.cpp painter.h
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c painter.cpp
