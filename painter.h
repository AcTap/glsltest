#ifndef _PAINTER_H
#define _PAINTER_H

#include <SDL2/SDL.h> // Библиотека SDL 2
#include <GL/glew.h>
#include <GL/glu.h> // Библиотека GLU
#include <iostream> // стандартная библиотека ввода-вывода в C++
#include <fstream>
using std::ifstream;
using std::ios;

class Painter{
 public:
  Painter(){};
  void init(int,int);
  int start();
  void DrawCube(float,float,float);
  ~Painter();
 private:
  SDL_Window *window;
  GLint      winH;
  GLint      winW;
  GLuint     GLProgramm;
  
};

unsigned long getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    
    unsigned long pos=file.tellg();
    file.seekg(0,ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);
    
    return len;
}

int loadshader(char* filename, GLchar** ShaderSource)
{
   ifstream file;
   file.open(filename, ios::in); // opens as ASCII!
   if(!file) return -1;
    
   unsigned int len = getFileLength(file);
    
   if (len==0) return -2;   // Error: Empty File 
    
   *ShaderSource = (GLchar*) new char[len+1];
   if (*ShaderSource == 0) return -3;   // can't reserve memory
   
    // len isn't always strlen cause some characters are stripped in ascii read...
    // it is important to 0-terminate the real length later, len is just max possible value... 
   *ShaderSource[len] = 0; 

   unsigned int i=0;
   while (file.good())
   {
       *ShaderSource[i] = file.get();       // get character from file.
       if (!file.eof())
        i++;
   }
    
   *ShaderSource[i] = 0;  // 0-terminate it at the correct position
    
   file.close();
      
   return 0; // No Error
}


void unloadshader(GLubyte** ShaderSource)
{
   if (*ShaderSource != 0)
     delete[] *ShaderSource;
   *ShaderSource = 0;
}
#endif _PAINTER_H
