#pragma once

#include <glad/glad.h>

#include <format>
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

class Shader {
private:
  GLuint _ID;
  static auto storeFileToString(const char *fileName) -> std::string;

public:
  explicit Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

  static auto deActivate() noexcept -> void;

  auto activate() const noexcept -> void;
  auto deleteProgram() const noexcept -> void;
  [[nodiscard]] auto getID() const noexcept -> GLuint;

  auto setBool(const char *name, bool value) const noexcept -> void;
  auto setInt(const char *name, int value) const noexcept -> void;
  auto setFloat(const char *name, float value) const noexcept -> void;
  auto setVec2(const char *name, const glm::vec2 &value) const noexcept -> void;
  auto setVec2(const char *name, float x, float y) const noexcept -> void;
  auto setVec3(const char *name, const glm::vec3 &value) const noexcept -> void;
  auto setVec3(const char *name, float x, float y, float z) const noexcept
      -> void;
  auto setVec4(const char *name, const glm::vec4 &value) const noexcept -> void;
  auto setVec4(const char *name, float x, float y, float z,
               float w) const noexcept -> void;
  auto setMat2(const char *name, const glm::mat2 &matrix) const noexcept
      -> void;
  auto setMat3(const char *name, const glm::mat3 &matrix) const noexcept
      -> void;
  auto setMat4(const char *name, const glm::mat4 &matrix) const noexcept
      -> void;
  auto setTextureUnit(const char *name, GLint unit) const noexcept
      -> void;
};
