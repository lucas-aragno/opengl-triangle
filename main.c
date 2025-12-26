#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include "shaders.h"
#include "mesh.h"

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char* vertexShaderSource = loadShaderFromFile("./shaders/default.vert");
  char* fragmentShaderSource = loadShaderFromFile("./shaders/default.frag");

  if(!vertexShaderSource || !fragmentShaderSource) {
    printf("Error loading shaders");
  }

  GLfloat vertices[] = {
    -0.5f, -0.5f * sqrtf(3.0f) * 1.0f / 3.0f, 0.0f,   0.8f, 0.3f,  0.02f,
     0.5f, -0.5f * sqrtf(3.0f) * 1.0f / 3.0f, 0.0f,   0.8f, 0.3f,  0.02f, 
    -0.25f, 0.5f * sqrtf(3.0f) * 1.0f / 6.0f, 0.0f,   0.9f, 0.45f, 0.17f,
     0.25f, 0.5f * sqrtf(3.0f) * 1.0f / 6.0f, 0.0f,   0.9f, 0.45f, 0.17f,
     0.0f, -0.5f * sqrtf(3.0f) * 1.0f / 3.0f, 0.0f,   0.8f, 0.3f,  0.02f
  };

  GLFWwindow* window = glfwCreateWindow(
    800,
    800,
    "triangle",
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
  Mesh triangle = createMesh(vertices, 3);

  linkMeshAttributes(
    triangle,
    1,
    3,
    GL_FLOAT,
    6 * sizeof(float),
    (void*)(3*sizeof(float))
  );

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    useShader(&shader);
    bindMesh(&triangle);
    glDrawArrays(GL_TRIANGLES, 0 , 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  free(vertexShaderSource);
  free(fragmentShaderSource);

  destroyShader(&shader);
  destroyMesh(&triangle);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}