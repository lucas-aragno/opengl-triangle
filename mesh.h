#ifndef MESH_H
#define MESH_H
  #include<glad/glad.h>

  typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei vertexCount;
  } Mesh;

  Mesh createMesh(
    const GLfloat *vertices,
    GLsizeiptr vertexBufferSize,
    GLsizei vertexCount,
    unsigned int* indices,
    GLsizeiptr indexBufferSize
  );
  
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