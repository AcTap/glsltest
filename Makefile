CPP=g++
CPPFLAGS=-Wall -std=c++11 -pedantic
LDFLAGS=- -lX11 -lGL -lGLU
OBJECTS=main.o painter.o
NAME=glsltest

$(NAME) : $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

main.o : main.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c main.cpp

painter.o : painter.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c painter.cpp
