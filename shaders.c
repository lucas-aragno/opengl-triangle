#include "shaders.h"

char* loadShaderFromFile(const char* path) {
  FILE *file = fopen(path, "rb");
  if(!file) {
    perror("fopen");
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size ,file);
  buffer[size] = '\0';

  fclose(file);

  return buffer;
}

static GLuint compileShader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "Shader compilation error:\n%s\n", log);
    }

    return shader;
}

Shader createShader(const char *vertex_src, const char *fragment_src) {
    Shader shader = {0};

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_src);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_src);

    shader.id = glCreateProgram();

    glAttachShader(shader.id, vs);
    glAttachShader(shader.id, fs);
    glLinkProgram(shader.id);

    GLint success;
    glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(shader.id, 512, NULL, log);
        fprintf(stderr, "Program link error:\n%s\n", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader;
}

void useShader(const Shader *shader) {
    glUseProgram(shader->id);
}

void destroyShader(Shader *shader) {
    glDeleteProgram(shader->id);
    shader->id = 0;
}
