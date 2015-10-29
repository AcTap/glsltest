#version 130
in vec2 a_Vertex;
out vec4 outcolor;
varying vec4 TexCoord;
uniform float xcenter;
uniform float ycenter;
uniform float scale;

void main(void)
{
        gl_Position = gl_ModelViewProjectionMatrix * vec4(a_Vertex,1.0,1.0);
        outcolor=vec4(1.0,0.8,0.2,1.0);
        TexCoord=gl_Position;
}

