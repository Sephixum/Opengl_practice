#include <VBO.hpp>

VBO::VBO(GLfloat *vertices, GLsizeiptr size) {

  glGenBuffers(1, &_ID);
  glBindBuffer(GL_ARRAY_BUFFER, _ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto VBO::bind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, _ID); }

auto VBO::unBind() noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto VBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &_ID); }
