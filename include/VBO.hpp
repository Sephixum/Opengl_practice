#pragma once

#include <glad/glad.h>

class VBO {
private:
  GLuint _ID;

public:
  explicit VBO(GLfloat *, GLsizeiptr);

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
};
