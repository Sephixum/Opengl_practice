#pragma once

#include "ShaderClass.hpp"
#include <glad/glad.h>

class Texture {
private:
  GLuint _ID;
  GLenum _type;
  GLenum _textureUnit;

public:
  explicit Texture() = default;
  explicit Texture(const char *image, GLenum textureType, GLenum slot,
                   GLenum pixeltype);

  auto bind() const noexcept -> void;
  auto activate() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteTexture() const noexcept -> void;
};
