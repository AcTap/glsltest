#include "painter.h"

unsigned long  Painter::getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    file.tellg();
    file.seekg(0,ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);

    return len;
}

string Painter::loadshader(string filename)
{
    string Shader;
   ifstream file;
   file.open(filename);
   if(!file) exit(1);

   while (file.good())
   {
       string temp;
       std::getline(file,temp);
       Shader.append(temp);
       Shader.append("\n");
   }
    file.close();

   return Shader;
}


void Painter::unloadshader(GLchar** ShaderSource)
{
   if (*ShaderSource != 0)
     delete[] *ShaderSource;
   *ShaderSource = 0;
}


Painter::~Painter()
{
}

Painter::Painter():window(nullptr){

}

void Painter::init(unsigned int width,unsigned int height)
{
  winW=width;
  winH=height;

  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){ 
    std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
    exit(1);
  } 
	
  // Включаем двойной буфер, настраиваем цвета
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  // Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.
  window = SDL_CreateWindow("GLSLtest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  //std::cout<<"wtf"<<"\n";
  glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL
  //std::cout<<"that's it"<<"\n";
  if(window == nullptr){	// если не получилось создать окно, то выходим
 	exit(1);
  }
//  std::cout<<"Shaders?"<<"\n";
  //shaders
  GLenum err = glewInit();
  if (err != GLEW_OK)
    exit(1); // or handle the error in a nicer way
  if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    exit(1); // or handle the error in a nicer way
  GLuint vertex=glCreateShader(GL_VERTEX_SHADER); 
  GLuint fragment=glCreateShader(GL_FRAGMENT_SHADER); 
  const string vert=loadshader("glsltest.vert");
  const string frag=loadshader("glsltest.frag");
  const GLchar* vertShader=vert.c_str();
  const GLchar* fragShader=frag.c_str();
  glShaderSource(vertex, 1,&vertShader, nullptr);
  glShaderSource(fragment, 1,&fragShader, nullptr);
  glCompileShader(vertex);
  GLint compOk;
  glGetShaderiv(vertex,GL_COMPILE_STATUS,&compOk);
  if(compOk!=GL_TRUE){
      GLsizei err;
      glGetShaderiv(vertex,GL_INFO_LOG_LENGTH,&err);
      char *infoLog=new char[err];
      glGetShaderInfoLog(vertex, err,nullptr,infoLog);
      std::cerr<<infoLog<<" in vertex"<<"\n";
      exit(1);
  }
  glCompileShader(fragment);
  glGetShaderiv(fragment,GL_COMPILE_STATUS,&compOk);
  if(compOk!=GL_TRUE){
      GLsizei err;
      glGetShaderiv(fragment,GL_INFO_LOG_LENGTH,&err);
      char *infoLog=new char[err];
      glGetShaderInfoLog(fragment, err,nullptr,infoLog);
      std::cerr<<infoLog<<" in fragment"<<"\n";
      exit(1);
  }

  GLProgramm = glCreateProgram();
  glAttachShader(GLProgramm,vertex);
  glAttachShader(GLProgramm,fragment);
  glLinkProgram(GLProgramm);
  int link_ok;
  glGetProgramiv(GLProgramm, GL_LINK_STATUS, &link_ok);
  if(!link_ok){
      std::cerr << "error link \n";
      GLsizei err;
      glGetProgramiv(GLProgramm, GL_INFO_LOG_LENGTH, &err);
      char *infoLog=new char[err];
      glGetProgramInfoLog(GLProgramm, err,nullptr,infoLog);
      std::cerr<<infoLog<<"\n";
      exit(1);
  }
  glUseProgram(GLProgramm);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST); // включаем тест глубины
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
  glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
}

int Painter::start()
{
  bool running = true;

  float xrf = 0, yrf = 0, zrf = 0; // углы поворота

  while(running){ 
    
    SDL_Event event; // события SDL
    
    while ( SDL_PollEvent(&event) ){ // начинаем обработку событий
      switch(event.type){ // смотрим:
      case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
	running = false;
	break;
	
      case SDL_KEYDOWN: // если нажата клавиша
	switch(event.key.keysym.sym){ // смотрим какая
	case SDLK_ESCAPE: // клавиша ESC
	  running = false; // завершаем работу программы
	  break;
					}
	break;
      } 
    }
    
    // пока программа запущена изменяем углы поворота, тем самым вращая куб
    
    xrf -= 0.5; 
    yrf -= 0.5;
    zrf -= 0.5;
    
    DrawCube(xrf, yrf, zrf); // рисуем сам куб с текущими углами поворота		
    // обновляем экран
    glFlush();
    SDL_GL_SwapWindow(window);
  }
  
  SDL_Quit(); // завершаем работу SDL и выходим
  return 0;
  
}



void Painter::DrawCube(float xrf, float yrf, float zrf)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана
  glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
  glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
  glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z
  GLuint VBOs[2];
  //std::cout<<"GenBuf"<<"\n";
  glGenBuffers(2, VBOs);
  //std::cout<<"BindBuf"<<"\n";
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  // Вершины нашего треугольника
  //std::cout<<"trig"<<"\n";
  GLfloat cube[24][3] = {
      {0,0,0},{1,0,0},{0.5,1,0.5},
      {0,0,0},{0,0,1},{0.5,1,0.5},
      {1,0,0},{1,0,1},{0.5,1,0.5},
      {0,0,1},{1,0,1},{0.5,1,0.5},

      {0,0,0},{1,0,0},{0.5,-1,0.5},
      {0,0,0},{0,0,1},{0.5,-1,0.5},
      {1,0,0},{1,0,1},{0.5,-1,0.5},
      {0,0,1},{1,0,1},{0.5,-1,0.5}
  };
  GLfloat colors[24][3]={
      {1,0,0},{0,1,0},{0,0,1},
      {1,0,0},{1,0,1},{0,0,1},
      {0,1,0},{1,1,0},{0,0,1},
      {1,0,1},{1,1,0},{0,0,1},

      {1,0,0},{0,1,0},{0,1,1},
      {1,0,0},{1,0,1},{0,1,1},
      {0,1,0},{1,1,0},{0,1,1},
      {1,0,1},{1,1,0},{0,1,1}
  };
  // Передаем вершины в буфер
  //std::cout<<"BufData"<<"\n";
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube)+sizeof(colors), nullptr, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(cube),cube);
  glBufferSubData(GL_ARRAY_BUFFER,sizeof(cube),sizeof(colors,colors),colors);
  //std::cout<<"draw"<<"\n";
  GLuint a_Vertex=glGetAttribLocation(GLProgramm,"a_Vertex");
  GLuint  a_color=glGetAttribLocation(GLProgramm,"a_color");
  //std::cout<<a_Vertex<<" location"<<"\n";
  glVertexAttribPointer(a_Vertex, 3, GL_FLOAT,GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(a_Vertex);
  glVertexAttribPointer(a_color, 3, GL_FLOAT,GL_FALSE, 0, BUFFER_OFFSET(sizeof(cube)));
  glEnableVertexAttribArray(a_color);
  glDrawArrays(GL_TRIANGLES, 0, 24);
}

void Painter::freeShader()
{
  glUseProgram(0);
  glDeleteProgram(GLProgramm);
}

void Painter::freeVBO(GLuint VBO)
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &VBO);
}
