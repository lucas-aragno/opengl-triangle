#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include "shaders.h"
#include "mesh.h"
#include "include/stb_image.h"

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char* vertexShaderSource = loadShaderFromFile("./shaders/square.vert");
  char* fragmentShaderSource = loadShaderFromFile("./shaders/square.frag");

  if(!vertexShaderSource || !fragmentShaderSource) {
    printf("Error loading shaders");
  }

  float vertices[] = {
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // 0: Bottom-Left
      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // 1: Bottom-Right
      0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // 2: Top-Right
      -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // 3: Top-Left
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLFWwindow* window = glfwCreateWindow(
    800,
    800,
    "square",
    NULL,
    NULL
  );

  if (window == NULL) {
    glfwTerminate();
    free(vertexShaderSource);
    free(fragmentShaderSource);
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();

  glViewport(0, 0, 800, 800);

  Shader shader = createShader(vertexShaderSource, fragmentShaderSource);
  Mesh square = createMesh(vertices, sizeof(vertices), sizeof(vertices), indices, sizeof(indices));

  linkMeshAttributes(
    square,
    0,
    3,
    GL_FLOAT,
    5 * sizeof(float),
    (void*)0
  );

  linkMeshAttributes(
    square,
    1,
    2,
    GL_FLOAT,
    5 * sizeof(float),
    (void*)(3* sizeof(float))
  );

  int width, height, numColCh;
  stbi_set_flip_vertically_on_load(1);
  unsigned char* bytes = stbi_load("./san.png", &width, &height, &numColCh, 4);

  if (bytes == NULL) {
      printf("ERROR: Could not find or load san.png\n");
  } else {
      printf("SUCCESS: Loaded %dx%d image\n", width, height);
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  GLenum format = (numColCh == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);  
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(bytes);

  glBindTexture(GL_TEXTURE_2D, 0);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    useShader(&shader);

    GLint tex0Loc = glGetUniformLocation(shader.id, "tex0");
    glUniform1i(tex0Loc, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    bindMesh(&square);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  free(vertexShaderSource);
  free(fragmentShaderSource);

  destroyShader(&shader);
  destroyMesh(&square);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}