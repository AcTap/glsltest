CC=clang
CFLAGS=-Wall -std=c++11 -Wunused-variable -I. 
LDFLAGS=-lSDL2 -lGL -lGLU -lX11 -lGLEW -lstdc++ 
DEPS=painter.h
SOURCES=main.cpp painter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/glsltest

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) $< -c -o $@ $(CFLAGS) 
