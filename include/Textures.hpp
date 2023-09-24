#pragma once

#include "ShaderClass.hpp"
#include <glad/glad.h>

class Texture {
private:
  GLuint _ID;
  GLenum _type;
  GLenum _textureUnit;

public:
  explicit Texture(const char *, GLenum, GLenum, GLenum) noexcept;

  void setTextureUnit(Shader &, const char *, GLint) const noexcept;
  void bind() const noexcept;
  void activate() const noexcept;
  void unBind() const noexcept;
  void deActivate() const noexcept;
  void deleteTexture() const noexcept;
};
