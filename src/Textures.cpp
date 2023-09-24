#include "Textures.hpp"
#include "stb_image.h"

Texture::Texture(const char *image, GLenum textureType, GLenum slot,
                 GLenum pixelType) noexcept
    : _type(textureType), _textureUnit(slot) {
  int widthImg, heightImg, numberOfColorChanels;
  GLubyte *bytes =
      stbi_load(image, &widthImg, &heightImg, &numberOfColorChanels, 0);
  std::cout << widthImg << "-------------\n";
  std::cout << heightImg << "-------------\n";
  std::cout << numberOfColorChanels << "------end-------\n";
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

    GLenum format = GL_RGBA;
    if (numberOfColorChanels == 3) {
      format = GL_RGB;
      std::cout << image << " has format GL_RGB \n";
    } else {
      format = GL_RGBA;
      std::cout << image << " has format GL_RGBA \n";
    }

    glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format,
                 pixelType, bytes);
    glGenerateMipmap(textureType);

    stbi_image_free(bytes);
    glBindTexture(textureType, 0);
  } else {
    std::cout << "texture " << image << " not loaded " << std::endl;
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
