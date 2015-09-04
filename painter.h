#ifndef _PAINTER_H
#define _PAINTER_H

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>


class Painter{
 public:
  Painter();
  void init(int,int);
  void DrawQuad();
  ~Painter();
 private:
  Display                 *dpy;
  Window                  root;
  const GLint             att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
  XVisualInfo             *vi;
  Colormap                cmap;
  XSetWindowAttributes    swa;
  Window                  win;
  GLXContext              glc;
  XWindowAttributes       gwa;
  XEvent                  xev;
  int                     winH;
  int                     winW;
  
}




#endif _PAINTER_H
