#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  GLuint id;
} Shader;

Shader createShader(const char* vertexSource, const char* fragmentShader);
void useShader(const Shader* shader);
void destroyShader(Shader *shader);
char* loadShaderFromFile(const char* path);

#endif