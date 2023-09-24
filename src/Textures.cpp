#include "Textures.hpp"
#include "stb_image.h"
#include <cstdlib>
#include <format>
#include <stdexcept>

Texture::Texture(const char *image, GLenum textureType, GLenum slot,
                 GLenum pixelType)
    : _type(textureType), _textureUnit(slot) {

  int widthImg, heightImg, numberOfColorChannels;
  GLubyte *bytes =
      stbi_load(image, &widthImg, &heightImg, &numberOfColorChannels, 0);

  if (bytes) {
    glGenTextures(1, &_ID);
    glActiveTexture(slot);
    glBindTexture(_type, _ID);

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format;
    switch (numberOfColorChannels) {
    case 3: {
      format = GL_RGB;
    } break;
    case 4: {
      format = GL_RGBA;
    } break;
    default: {
      throw std::runtime_error(
          std::format("Texture format not supported for {}", image));
    } break;
    }

    glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format,
                 pixelType, bytes);
    glGenerateMipmap(textureType);

    stbi_image_free(bytes);
    glBindTexture(textureType, 0);
  } else {
    throw std::runtime_error(
        std::format("Texture {} could not be loaded", image));
  }
}

auto Texture::setTextureUnit(Shader &shaderProgram, const char *uniformName,
                             GLint unit) const noexcept -> void {

  shaderProgram.activate();
  glUniform1i(glGetUniformLocation(shaderProgram.getID(), uniformName), unit);
  shaderProgram.deActivate();
}

auto Texture::bind() const noexcept -> void { glBindTexture(_type, _ID); }

auto Texture::activate() const noexcept -> void {

  glActiveTexture(_textureUnit);
}

auto Texture::unBind() const noexcept -> void { glBindTexture(_type, 0); }

auto Texture::deActivate() const noexcept -> void { glDisable(_textureUnit); }

auto Texture::deleteTexture() const noexcept -> void {

  glDeleteTextures(1, &_ID);
}
