#version 130
in vec3 a_Vertex;
in vec3 a_color;
out vec4 outcolor;
void main(void)
{
        gl_Position = gl_ModelViewProjectionMatrix * vec4(a_Vertex,1.0);
        outcolor=vec4(a_color,1.0);
}
