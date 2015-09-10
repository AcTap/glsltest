#ifndef _PAINTER_H
#define _PAINTER_H
#define BUFFER_OFFSET(offset) ((void *)(offset))
#include <SDL2/SDL.h> // Библиотека SDL 2
#include <GL/glew.h>
#include <GL/glu.h> // Библиотека GLU
#include <GL/gl.h>
#include <iostream> // стандартная библиотека ввода-вывода в C++
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ios;

class Painter{
 public:
  Painter();
  void init(unsigned int, unsigned int);
  int start();
  void DrawCube(float,float,float);
  ~Painter();
 private:
  SDL_Window *window;
  GLuint      winH;
  GLuint      winW;
  GLuint     GLProgramm;
  SDL_GLContext glcontext;
  
  void unloadshader(GLchar **ShaderSource);
  string loadshader(string filename);
  unsigned long getFileLength(ifstream &file);
  void freeShader();
  void freeVBO();
  void freeVBO(GLuint VBO);
};
#endif // _PAINTER_H
