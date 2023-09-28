#pragma once

#include <VBO.hpp>
#include <glad/glad.h>

class VAO {
private:
  GLuint _ID;

public:
  explicit VAO() noexcept;

  void linkVBO(VBO &, GLuint, GLuint, GLenum, GLsizeiptr,
               void *) const noexcept;
  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteAttr() const noexcept -> void;
};
