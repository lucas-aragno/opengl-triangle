#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <cglm/cglm.h>
#include<math.h>
#include "shaders.h"
#include "mesh.h"
#include "include/stb_image.h"
#include "camera.h"

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

/*
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // 0: Bottom-Left
      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // 1: Bottom-Right
      0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // 2: Top-Right
      -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // 3: Top-Left
  };
*/

  float vertices[] = {
    -0.5f, -0.0f, 0.5f,   0.0f, 0.0f, 
    -0.5f, 0.0f, -0.5f,   5.0f, 0.0f, 
    0.5f,  0.0f, -0.5f,   0.0f, 0.0f,
    0.5f,  0.0f, 0.5f,   5.0f, 1.0f,
    0.0f,  0.8f, 0.0f,   2.5f, 5.0f
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
  };

  GLFWwindow* window = glfwCreateWindow(
    800,
    800,
    "square",
    NULL,
    NULL
  );

  mat4 model;
  mat4 view;
  mat4 proj;

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

  float rotation = 0.0f;
  double prevTime = glfwGetTime();

  glEnable(GL_DEPTH_TEST);
  
  Camera camera = {0};

  camera.width = 800;
  camera.height = 800;


camera.speed = 0.01f;
camera.sensitivity = 100.0f;

glm_vec3_copy((vec3){0.0f, 0.0f, 2.5f}, camera.position);
glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera.orientation);
glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera.up);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    //glm_mat4_identity(view);
   //glm_mat4_identity(proj);
    glm_mat4_identity(model);

    glm_rotate(model, rotation, (vec3) { 0.0f, 1.0f, 0.0f});
    glm_translate(view, (vec3){ 0.0f, -0.5f, -2.0f });

    glm_perspective(
        glm_rad(45.0f),
        800.0f / 800.0f,
        0.1f,
        100.0f,
        proj
    );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    useShader(&shader);

    cam_matrix(
      &camera,
      45.0f,
      0.1f,
      100.0f,
      &shader,
      "camMatrix"
    );

    cam_input(window, &camera);

    double crntTime = glfwGetTime();
    double delta = crntTime - prevTime;
    prevTime = crntTime;

    float rotationSpeed = 0.3f; // degrees per second
    rotation += rotationSpeed * delta;

    GLint tex0Loc = glGetUniformLocation(shader.id, "tex0");
    //GLint modelLoc = glGetUniformLocation(shader.id, "model");
   // GLint viewLoc = glGetUniformLocation(shader.id, "view");
    //GLint projLoc = glGetUniformLocation(shader.id, "proj");

    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);
    //glUniformMatrix4fv(viewLoc,  1, GL_FALSE, (float*)view);
    //glUniformMatrix4fv(projLoc,  1, GL_FALSE, (float*)proj);

    glUniform1i(tex0Loc, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    bindMesh(&square);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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