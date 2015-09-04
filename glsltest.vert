#version 120

in vect3 color;
out vect4 outcolor;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	outcolor=vect4(color,0.1);
}