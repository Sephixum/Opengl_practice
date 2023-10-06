#include <ShaderClass.hpp>

auto Shader::storeFileToString(const char *fileName) -> std::string {

  std::ifstream file(fileName, std::ios::binary);
  if (file) {
    return std::string{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};
  }
  throw std::runtime_error(
      std::format("There is no file with path \"{}\".\n", fileName));
}

Shader::Shader(const char *vertexShaderFile, const char *fragmentShaderFile) {

  std::string vertexCode;
  std::string fragmentCode;
  try {
    vertexCode = storeFileToString(vertexShaderFile);
    fragmentCode = storeFileToString(fragmentShaderFile);
  } catch (std::exception &e) {
    std::cerr << "Caught an exception: " << e.what();
    std::exit(1);
  }

  auto vertexSource = vertexCode.c_str();
  auto fragmentSource = fragmentCode.c_str();

  int success;
  char infoLog[512];

  auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << std::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                             "File : {}\n"
                             "Info : {}\n",
                             vertexShaderFile, infoLog);
  } else {
    std::cout << std::format("Vertex shader \"{}\" compiled successfully.\n",
                             vertexShaderFile);
  }

  auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::puts(std::format("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                          "File : {}\n"
                          "Info : {}\n",
                          fragmentShaderFile, infoLog)
                  .c_str());
  } else {
    std::puts(std::format("fragment shader \"{}\" compiled successfully.\n",
                          fragmentShaderFile)
                  .c_str());
  }

  _ID = glCreateProgram();
  glAttachShader(_ID, vertexShader);
  glAttachShader(_ID, fragmentShader);
  glLinkProgram(_ID);
  glGetProgramiv(_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER:PROGRAM::LINKING_FAILED\n" << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

auto Shader::activate() const noexcept -> void { glUseProgram(_ID); }

auto Shader::deActivate() const noexcept -> void { glUseProgram(0); }

auto Shader::deleteProgram() const noexcept -> void { glDeleteProgram(_ID); }

auto Shader::getID() const noexcept -> GLuint { return _ID; }

auto Shader::setBool(const char *name, bool value) const noexcept -> void {

  glUniform1i(glGetUniformLocation(_ID, name), static_cast<int>(value));
}

auto Shader::setInt(const char *name, int value) const noexcept -> void {

  glUniform1i(glGetUniformLocation(_ID, name), value);
}

auto Shader::setFloat(const char *name, float value) const noexcept -> void {

  glUniform1f(glGetUniformLocation(_ID, name), value);
}

auto Shader::setVec2(const char *name, const glm::vec2 &value) const noexcept
    -> void {

  glUniform2fv(glGetUniformLocation(_ID, name), 1, glm::value_ptr(value));
}

auto Shader::setVec2(const char *name, float x, float y) const noexcept
    -> void {

  glUniform2f(glGetUniformLocation(_ID, name), x, y);
}

auto Shader::setVec3(const char *name, const glm::vec3 &value) const noexcept
    -> void {

  glUniform3fv(glGetUniformLocation(_ID, name), 1, glm::value_ptr(value));
}

auto Shader::setVec3(const char *name, float x, float y, float z) const noexcept
    -> void {

  glUniform3f(glGetUniformLocation(_ID, name), x, y, z);
}

auto Shader::setVec4(const char *name, const glm::vec4 &value) const noexcept
    -> void {

  glUniform4fv(glGetUniformLocation(_ID, name), 1, glm::value_ptr(value));
}

auto Shader::setVec4(const char *name, float x, float y, float z,
                     float w) const noexcept -> void {

  glUniform4f(glGetUniformLocation(_ID, name), x, y, z, w);
}

auto Shader::setMat2(const char *name, const glm::mat2 &matrix) const noexcept
    -> void {

  glUniformMatrix2fv(glGetUniformLocation(_ID, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setMat3(const char *name, const glm::mat3 &matrix) const noexcept
    -> void {

  glUniformMatrix3fv(glGetUniformLocation(_ID, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setMat4(const char *name, const glm::mat4 &matrix) const noexcept
    -> void {

  glUniformMatrix4fv(glGetUniformLocation(_ID, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setTextureUnit(const char *name, GLint unit) const noexcept
    -> void {

  glUniform1i(glGetUniformLocation(_ID, name), unit);
}
