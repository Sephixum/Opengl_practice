#include <EBO.hpp>

EBO::EBO(GLuint *indices, GLsizeiptr size) noexcept {
  glGenBuffers(1, &_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::bind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

auto EBO::unBind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &_ID); }
