#pragma once

#include <glad/glad.h>
#include <stdio.h>

#include "../../../utils/utils.h"

static GLuint compileShader(GLenum type, const char* source);
static GLuint createShaderProgram(GLuint vertex, GLuint fragment);
GLuint shader_create(const char* vertexCodePath, const char* fragmentCodePath);