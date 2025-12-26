#ifndef CAMERA_H
#define CAMERA_H

  #include<glad/glad.h>
  #include <cglm/cglm.h>
  #include<GLFW/glfw3.h>
  #include "shaders.h"

  typedef struct {
    vec3 position;
    vec3 orientation;
    vec3 up;
    int width;
    int height;
    float speed;
    float sensitivity;
  } Camera;

void cam_matrix(Camera* camera,
                float FOVdegree,
                float nearPlane,
                float farPlane,
                Shader* shader,
                const char* uniform);
void cam_input(GLFWwindow* window, Camera* camera);
#endif