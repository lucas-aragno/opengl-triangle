#include "camera.h"


void cam_matrix(Camera* camera,
                float FOVdegree,
                float nearPlane,
                float farPlane,
                Shader* shader,
                const char* uniform)
{
    mat4 view;
    mat4 projection;
    mat4 pv;
    vec3 center;

    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    // center = position + orientation
    glm_vec3_add(camera->position, camera->orientation, center);

    glm_lookat(camera->position, center, camera->up, view);

    glm_perspective(
        glm_rad(FOVdegree),
        (float)camera->width / (float)camera->height,
        nearPlane,
        farPlane,
        projection
    );

    glm_mat4_mul(projection, view, pv);

    glUniformMatrix4fv(
        glGetUniformLocation(shader->id, uniform),
        1,
        GL_FALSE,
        (float*)pv
    );
}


void cam_input(GLFWwindow* window, Camera* camera) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3 velocity;
        glm_vec3_scale(camera->orientation, camera->speed, velocity);
        glm_vec3_add(camera->position, velocity, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3 velocity;
        glm_vec3_scale(camera->orientation, camera->speed, velocity);
        glm_vec3_sub(camera->position, velocity, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
    {
        vec3 right;
        vec3 moveDir;

        glm_vec3_cross(camera->orientation, camera->up, right);

        glm_vec3_normalize(right);

        float moveSpeed = -camera->speed;
        glm_vec3_scale(right, moveSpeed, moveDir);

        glm_vec3_add(camera->position, moveDir, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
    {
        vec3 right;
        vec3 moveDir;

        glm_vec3_cross(camera->orientation, camera->up, right);

        glm_vec3_normalize(right);

        float moveSpeed = -camera->speed;
        glm_vec3_scale(right, moveSpeed, moveDir);

        glm_vec3_sub(camera->position, moveDir, camera->position);
    }
}
