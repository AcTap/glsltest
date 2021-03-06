#version 130
precision highp float;
in vec4 outcolor;
varying vec4 TexCoord;
uniform vec3 data;
vec2 c_mult(in vec2 a,in vec2 b) {
  return vec2(a.x * b.x - a.y * b.y, a.x * b.y+a.y * b.x );
}
vec2 c_pow(in vec2 a,in int b){
  int i=1;
  vec2 z=a;
  for (;i<b;i++){
    z=c_mult(z,a);
  }
  return z;
}
vec2 divide(in vec2 a,in vec2 b){
  return vec2(a.x*b.x+a.y*b.y,b.x*a.y-a.x*b.y)/dot(b,b);
}
vec4 getColor(in vec4 z){
  int depth=64;
  int i=depth;
  vec2 C=vec2(0.67,0.4);
  vec2 pos=z.xy;
  pos=pos*data.z-data.xy;
  vec2 con=pos;
  while(i-->0){
    if(dot(pos,pos)>4.0) break;
      pos=pos-divide(c_mult(c_pow(pos,4),C)-pos+C,4*c_mult(c_pow(pos,3),C)); 
      //pos=c_pow(pos,2)+con;
  }
  float n = i;
  vec4 color=vec4(0,0,0,1.0);
  color.r=cos(1.0-n/depth);
  color.g=sqrt(n/depth);
  color.b=sin((1.0-n/depth));
  return color;
}

void main(void)
{
  gl_FragColor=outcolor*getColor(TexCoord);
}
