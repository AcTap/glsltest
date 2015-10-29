#version 130
in vec2 a_Vertex;
in vec3 a_color;
out vec4 outcolor;
uniform float xcenter;
uniform float ycenter;
uniform float scale;
vec2 c_mult(vec2 a, vec2 b) {
  return vec2(a.x * b.x - a.y * b.y, a.x * b.y+a.y * b.x );
}
vec2 c_pow(vec2 a, int b){
  int i=1;
  vec2 z=a;
  for (;i<b;i++){
    z=c_mult(z,a);
  }
  return z;
}
float dot(vec2 a, vec2 b){
  return a.x*b.x+a.y*b.y;
}
vec2 divide(vec2 a,vec2 b){
  return vec2(a.x*b.x+a.y*b.y,b.x*a.y-a.x*b.y)/dot(b,b);
}
float getColor(vec2 pos){
  int depth=512;
  int i=depth;
  vec2 C=vec2(0.7,0.4);
  pos=pos*scale-scale*vec2(xcenter,ycenter);
  vec2 con=pos;
  while(i-->0){
    if(dot(pos,pos)<=4.0)
      pos=pos-divide(c_mult(c_pow(pos,4),C)-pos+C,4*c_mult(c_pow(pos,3),C)); 
      //pos=c_pow(pos,3)+con;
    else{
      break;
    }
  }
  float n = i;
  return 1.0-n/depth;
}

void main(void)
{
        gl_Position = gl_ModelViewProjectionMatrix * vec4(a_Vertex,1.0,1.0);
        outcolor=getColor(vec2(gl_Position.x,gl_Position.y))*vec4(1.0,0.8,0.2,1.0)+(1.0-getColor(vec2(gl_Position.x,gl_Position.y)))*vec4(0.1,0.05,0.8,1.0);
}

