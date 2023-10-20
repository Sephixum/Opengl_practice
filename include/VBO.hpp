#pragma once

#include <glad/glad.h>

class VBO {
private:
  GLuint _ID;

public:
  explicit VBO(GLfloat *vertices, GLsizeiptr size);

  auto bind() const noexcept -> void;
  static auto unBind() noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
};
