#pragma once

#include <VBO.hpp>
#include <glad/glad.h>

class VAO {
private:
  GLuint _ID;

public:
  explicit VAO() noexcept;

  void linkVBO(VBO &vbo, GLuint layout, GLuint numOfComponents,
               GLenum typeOfComponenets, GLsizeiptr stride,
               void *offSet) const noexcept;
  auto bind() const noexcept -> void;
  static auto unBind() noexcept -> void;
  auto deleteAttr() const noexcept -> void;
};
