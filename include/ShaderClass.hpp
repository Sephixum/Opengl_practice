#pragma once

#include <glad/glad.h>

#include <format>
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

auto get_file_contents(const char *fileName) -> std::string;

class Shader {
private:
  GLuint _ID;

public:
  explicit Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteProgram() const noexcept -> void;
  auto getID() const noexcept -> GLuint;

  auto setBool(const std::string &name, bool value) const noexcept -> void;
  auto setInt(const std::string &name, int value) const noexcept -> void;
  auto setFloat(const std::string &name, float value) const noexcept -> void;
  auto setVec2(const std::string &name, const glm::vec2 &value) const noexcept
      -> void;
  auto setVec2(const std::string &name, float x, float y) const noexcept
      -> void;
  auto setVec3(const std::string &name, const glm::vec3 &value) const noexcept
      -> void;
  auto setVec3(const std::string &name, float x, float y,
               float z) const noexcept -> void;
  auto setVec4(const std::string &name, const glm::vec4 &value) const noexcept
      -> void;
  auto setVec4(const std::string &name, float x, float y, float z,
               float w) const noexcept -> void;
  auto setMat2(const std::string &name, const glm::mat2 &matrix) const noexcept
      -> void;
  auto setMat3(const std::string &name, const glm::mat3 &matrix) const noexcept
      -> void;
  auto setMat4(const std::string &name, const glm::mat4 &matrix) const noexcept
      -> void;
};
