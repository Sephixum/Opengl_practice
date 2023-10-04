#include <ShaderClass.hpp>

auto get_file_contents(const char *fileName) -> std::string {

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
    vertexCode = get_file_contents(vertexShaderFile);
    fragmentCode = get_file_contents(fragmentShaderFile);
  } catch (std::runtime_error &e) {
    std::cerr << "Caught an exception: " << e.what();
    std::exit(1);
  }

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  int success;
  std::string infoLog;

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  _ID = glCreateProgram();
  glAttachShader(_ID, vertexShader);
  glAttachShader(_ID, fragmentShader);
  glLinkProgram(_ID);
  glGetProgramiv(_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_ID, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER:PROGRAM::LINKING_FAILED\n" << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

auto Shader::activate() const noexcept -> void { glUseProgram(_ID); }

auto Shader::deActivate() const noexcept -> void { glUseProgram(0); }

auto Shader::deleteProgram() const noexcept -> void { glDeleteProgram(_ID); }

auto Shader::getID() const noexcept -> GLuint { return _ID; }

auto Shader::setBool(const std::string &name, bool value) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(_ID, name.c_str()), static_cast<int>(value));
}

auto Shader::setInt(const std::string &name, int value) const noexcept -> void {
  glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

auto Shader::setFloat(const std::string &name, float value) const noexcept
    -> void {
  glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

auto Shader::setVec2(const std::string &name,
                     const glm::vec2 &value) const noexcept -> void {
  glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1,
               glm::value_ptr(value));
}

auto Shader::setVec2(const std::string &name, float x, float y) const noexcept
    -> void {
  glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}

auto Shader::setVec3(const std::string &name,
                     const glm::vec3 &value) const noexcept -> void {
  glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1,
               glm::value_ptr(value));
}

auto Shader::setVec3(const std::string &name, float x, float y,
                     float z) const noexcept -> void {
  glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}

auto Shader::setVec4(const std::string &name,
                     const glm::vec4 &value) const noexcept -> void {
  glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1,
               glm::value_ptr(value));
}

auto Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const noexcept -> void {
  glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
}

auto Shader::setMat2(const std::string &name,
                     const glm::mat2 &matrix) const noexcept -> void {
  glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setMat3(const std::string &name,
                     const glm::mat3 &matrix) const noexcept -> void {
  glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setMat4(const std::string &name,
                     const glm::mat4 &matrix) const noexcept -> void {
  glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto Shader::setTextureUnit(const std::string &name, GLint unit) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(_ID, name.c_str()), unit);
}
