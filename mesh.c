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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);

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
  GLsizeiptr vertexBufferSize,
  GLsizei vertexCount,
  unsigned int* indices,
  GLsizeiptr indexBufferSize
) {
  Mesh mesh = {0};
  mesh.vertexCount = vertexCount;

  glGenVertexArrays(1, &mesh.vao);
  glGenBuffers(1, &mesh.vbo);
  glBindVertexArray(mesh.vao);
  glGenBuffers(1, &mesh.ebo);

  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);

  glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertices, GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return mesh;
}

void bindMesh(const Mesh *mesh) {
  glBindVertexArray(mesh->vao);
}

void destroyMesh(Mesh *mesh) {
  glDeleteVertexArrays(1, &mesh->vao);
  glDeleteBuffers(1, &mesh->vbo);
  glDeleteBuffers(1, &mesh->ebo);
  mesh->vao = 0;
  mesh->vbo = 0;
  mesh->ebo = 0;
}