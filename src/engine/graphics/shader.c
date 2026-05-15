#include "shader.h"

static GLuint compileShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint sucess;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

  if(!sucess){
    char infoLog[512];

    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    glDeleteShader(shader);

    printf("Erro na compilacao do Shader: \n%s\n", infoLog);
    return 0;
  }

  return shader;
}

static GLuint createShaderProgram(GLuint vertex, GLuint fragment) {
  GLuint program = glCreateProgram();

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);
  
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  GLint sucess;

  glGetProgramiv(program, GL_LINK_STATUS, &sucess);

  if(!sucess){
    char infoLog[512];

    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("Erro na link do Shader Program: \n%s\n", infoLog);
    return 0;
  }

  if(program == 0){
    printf("Erro ao criar shader program!\n");
  }

  return program;
}

GLuint shader_create(const char* vertexCodePath, const char* fragmentCodePath) {
  char* vertexShaderCode = readFile(vertexCodePath);
  char* fragmentShaderCode = readFile(fragmentCodePath);

  GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
  GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

  free(vertexShaderCode);
  free(fragmentShaderCode);

  if(vertex == 0 || fragment == 0){
    printf("Erro: shader invalido!\n");
    return 0;
  }

  return createShaderProgram(vertex, fragment);
}