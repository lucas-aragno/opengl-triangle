#ifndef MESH_H
#define MESH_H
  #include<glad/glad.h>

  typedef struct {
    GLuint vao;
    GLuint vbo;
    GLsizei vertexCount;
  } Mesh;

  Mesh createMesh(const GLfloat *vertices, GLsizei vertexCount);
  void bindMesh(const Mesh* mesh);
  void destroyMesh(Mesh *mesh);
  void linkMeshAttributes(
    Mesh mesh,
    GLuint layout,
    GLint size,
    GLenum type,
    GLsizei stride,
    const void *pointer
  );
#endif