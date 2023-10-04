#pragma once

#include <glad/glad.h>

class EBO {
private:
  GLuint _ID;

public:
  explicit EBO(GLuint *indices, GLsizeiptr size) noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
};
