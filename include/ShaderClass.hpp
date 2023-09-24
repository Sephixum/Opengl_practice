#pragma once

#include <glad/glad.h>

#include <format>
#include <fstream>
#include <iostream>
#include <string>

auto get_file_contents(const char *fileName) -> std::string;

class Shader {
private:
  GLuint _ID;

public:
  explicit Shader(const char *, const char *);

  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteProgram() const noexcept -> void;
  auto setUniformValue(const char *, float) const noexcept -> void;
  auto getID() const noexcept -> GLuint;
};
