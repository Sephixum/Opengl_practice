#include <VAO.hpp>

VAO::VAO() noexcept { glGenVertexArrays(1, &_ID); }

void VAO::linkVBO(VBO &vbo, GLuint layout, GLuint numOfComponents,
                  GLenum typeOfComponents, GLsizeiptr stride,
                  void *offSet) const noexcept {

  vbo.bind();
  glVertexAttribPointer(layout, numOfComponents, typeOfComponents, GL_FALSE,
                        stride, offSet);
  glEnableVertexAttribArray(layout);
  vbo.unBind();
}

auto VAO::bind() const noexcept -> void { glBindVertexArray(_ID); }

auto VAO::unBind() noexcept -> void { glBindVertexArray(0); }

auto VAO::deleteAttr() const noexcept -> void { glDeleteVertexArrays(1, &_ID); }
