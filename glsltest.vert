#version 130

uniform mat4 modelviewprojectionMatrix;

in vect3 position;
in vect3 color;
out vect4 outcolor;

void main(void)
{
	gl_Position=modelviewprojectionMatrix*vect4(position,1.0);
	outcolor=vect4(color,0.1);
}