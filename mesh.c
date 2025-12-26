#include "mesh.h"


void linkMeshAttributes(
  Mesh mesh,
  GLuint layout,
  GLint size,
  GLenum type,
  GLsizei stride,
  const void *pointer
) {
  glBindVertexArray(mesh.vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  glVertexAttribPointer(
    layout,
    size,
    type,
    GL_FALSE,
    stride,
    pointer
  );

  glEnableVertexAttribArray(layout);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Mesh createMesh(
  const GLfloat *vertices,
  GLsizei vertexCount
) {
  Mesh mesh = {0};
  mesh.vertexCount = vertexCount;

  glGenVertexArrays(1, &mesh.vao);
  glGenBuffers(1, &mesh.vbo);

  glBindVertexArray(mesh.vao);

  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    6 * sizeof(float),
    (void*) 0
  );

  /*
  glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    6 * sizeof(float),
    (void*)(3 * sizeof(float))
  );*/

  glEnableVertexAttribArray(0);
  //glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return mesh;
}


void bindMesh(const Mesh *mesh) {
  glBindVertexArray(mesh->vao);
}

void destroyMesh(Mesh *mesh) {
  glDeleteVertexArrays(1, &mesh->vao);
  glDeleteBuffers(1, &mesh->vbo);
  mesh->vao = 0;
  mesh->vbo = 0;
}